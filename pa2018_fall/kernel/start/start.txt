
start.o:     file format elf32-i386


Disassembly of section .text:

00000000 <start>:
   0:	0f 01 15 4c 00 00 40 	lgdtl  0x4000004c
   7:	0f 20 c0             	mov    %cr0,%eax
   a:	83 c8 01             	or     $0x1,%eax
   d:	0f 22 c0             	mov    %eax,%cr0
  10:	ea 17 00 00 40 08 00 	ljmp   $0x8,$0x40000017

00000017 <start_cond>:
  17:	66 b8 10 00          	mov    $0x10,%ax
  1b:	8e d8                	mov    %eax,%ds
  1d:	8e c0                	mov    %eax,%es
  1f:	8e d0                	mov    %eax,%ss
  21:	bd 00 00 00 00       	mov    $0x0,%ebp
  26:	bc 00 00 00 08       	mov    $0x8000000,%esp
  2b:	83 ec 10             	sub    $0x10,%esp
  2e:	e9 fc ff ff ff       	jmp    2f <start_cond+0x18>
  33:	90                   	nop

00000034 <gdt>:
	...
  3c:	ff                   	(bad)  
  3d:	ff 00                	incl   (%eax)
  3f:	00 00                	add    %al,(%eax)
  41:	9a cf 00 ff ff 00 00 	lcall  $0x0,$0xffff00cf
  48:	00                   	.byte 0x0
  49:	92                   	xchg   %eax,%edx
  4a:	cf                   	iret   
	...

0000004c <gdtdesc>:
  4c:	17                   	pop    %ss
  4d:	00 34 00             	add    %dh,(%eax,%eax,1)
  50:	00                   	.byte 0x0
  51:	40                   	inc    %eax
