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
	subq $4, %rsp
	movl $5, -4(%rbp)
	movl $1, %eax
	movl -4(%rbp), %ebx
	int $0x80
	leave
	ret
