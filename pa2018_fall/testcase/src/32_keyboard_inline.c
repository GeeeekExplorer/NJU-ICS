const char str[] = "Keyboard Testing!\n";

int main() {
	while(1) {
	asm volatile (	"movl $4, %eax;" // system call ID, 4 = SYS_write
			"movl $1, %ebx;" // file descriptor, 1 = stdout
			"movl $str, %ecx;" // buffer address
			"movl $19, %edx;" // length
			"int $0x80;"
			"hlt;" ); // wait until an interrupt comes
	}
	return 0;
}
