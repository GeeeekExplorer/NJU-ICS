#include "nemu.h"
#include <stdlib.h>
#include <elf.h>

//char *exec_file = NULL;

static char *strtab = NULL;
static Elf32_Sym *symtab = NULL;
static int nr_symtab_entry;

void load_elf_tables(char * exec_file) {
	FILE *fp = fopen(exec_file, "rb");
	// Assert(fp, "file '%s' not exist!", exec_file);
	assert(fp);

	uint8_t buf[4096];
	/* Read the first 4096 bytes from the exec_file.
	 * They should contain the ELF header and program headers. */
	fread(buf, 4096, 1, fp);

	/* The first several bytes contain the ELF header. */
	Elf32_Ehdr *elf = (void *)buf;
	char magic[] = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3};

	/* Check ELF header */
	assert(memcmp(elf->e_ident, magic, 4) == 0);		// magic number
	assert(elf->e_ident[EI_CLASS] == ELFCLASS32);		// 32-bit architecture
	assert(elf->e_ident[EI_DATA] == ELFDATA2LSB);		// littel-endian
	assert(elf->e_ident[EI_VERSION] == EV_CURRENT);		// current version
	assert(elf->e_ident[EI_OSABI] == ELFOSABI_SYSV || 	// UNIX System V ABI
			elf->e_ident[EI_OSABI] == ELFOSABI_LINUX); 	// UNIX - GNU
	assert(elf->e_ident[EI_ABIVERSION] == 0);			// should be 0
	assert(elf->e_type == ET_EXEC);						// executable file
	assert(elf->e_machine == EM_386);					// Intel 80386 architecture
	assert(elf->e_version == EV_CURRENT);				// current version


	/* Load symbol table and string table for future use */

	/* Load section header table */
	uint32_t sh_size = elf->e_shentsize * elf->e_shnum;
	Elf32_Shdr *sh = malloc(sh_size);
	fseek(fp, elf->e_shoff, SEEK_SET);
	fread(sh, sh_size, 1, fp);

	/* Load section header string table */
	char *shstrtab = malloc(sh[elf->e_shstrndx].sh_size);
	fseek(fp, sh[elf->e_shstrndx].sh_offset, SEEK_SET);
	fread(shstrtab, sh[elf->e_shstrndx].sh_size, 1, fp);

	int i;
	for(i = 0; i < elf->e_shnum; i ++) {
		if(sh[i].sh_type == SHT_SYMTAB && 
				strcmp(shstrtab + sh[i].sh_name, ".symtab") == 0) {
			/* Load symbol table from exec_file */
			symtab = malloc(sh[i].sh_size);
			fseek(fp, sh[i].sh_offset, SEEK_SET);
			fread(symtab, sh[i].sh_size, 1, fp);
			nr_symtab_entry = sh[i].sh_size / sizeof(symtab[0]);
		}
		else if(sh[i].sh_type == SHT_STRTAB && 
				strcmp(shstrtab + sh[i].sh_name, ".strtab") == 0) {
			/* Load string table from exec_file */
			strtab = malloc(sh[i].sh_size);
			fseek(fp, sh[i].sh_offset, SEEK_SET);
			fread(strtab, sh[i].sh_size, 1, fp);
		}
	}

	free(sh);
	free(shstrtab);

	assert(strtab != NULL && symtab != NULL);

	fclose(fp);
}

uint32_t look_up_fun_symtab(char *sym, bool *success) {
	int i;
	for(i = 0; i < nr_symtab_entry; i ++) {
		uint8_t type = ELF32_ST_TYPE(symtab[i].st_info);
		if(type == STT_FUNC && strcmp(strtab + symtab[i].st_name, sym) == 0) {
			*success = true;
			return symtab[i].st_value;
		}
	}

	*success = false;
	return 0;
}

uint32_t look_up_symtab(char *sym, bool *success) {
	int i;
	for(i = 0; i < nr_symtab_entry; i ++) {
		uint8_t type = ELF32_ST_TYPE(symtab[i].st_info);
		if((type == STT_FUNC || type == STT_OBJECT) && 
				strcmp(strtab + symtab[i].st_name, sym) == 0) {
			*success = true;
			return symtab[i].st_value;
		}
	}

	*success = false;
	return 0;
}

const char* find_fun_name(uint32_t eip) {
	static const char not_found[] = "???";

	int i;
	for(i = 0; i < nr_symtab_entry; i ++) {
		if(ELF32_ST_TYPE(symtab[i].st_info) == STT_FUNC && 
				eip >= symtab[i].st_value && eip < symtab[i].st_value + symtab[i].st_size) {
			return strtab + symtab[i].st_name;
		}
	}

	return not_found;
}
