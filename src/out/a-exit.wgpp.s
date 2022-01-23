.text
.section .rodata
	.globl main
	.type main, @function
	.printnum:
		.string "%d"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $1, %eax
	movl $0, %ebx
	int $0x80
	leave
	ret
