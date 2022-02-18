.text
.section .rodata
	.globl main
	.type main, @function
	.printnum:
		.string "%d\n"
		.text
	.printchr:
		.string "%c\n"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	movl $-12, -4(%rbp)
	subq $4, %rsp
	movl $'j', -5(%rbp)
	subq $4, %rsp
	movl $'d', -6(%rbp)
	subq $4, %rsp
	movl $'p', -7(%rbp)
	subq $4, %rsp
	movl $12, -4(%rbp)
	movq $60, %rax
	movslq -4(%rbp), %rdi
	syscall
	leave
	ret
