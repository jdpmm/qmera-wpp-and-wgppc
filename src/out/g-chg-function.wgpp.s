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
	movl $16, -4(%rbp)
	subq $4, %rsp
	movl $2022, -8(%rbp)
	movl $-16, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl -8(%rbp), %eax
	movl %eax, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $0, %r14d
	movl $2022, %r14d
	subl -4(%rbp), %r14d
	movl %r14d, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $1, %eax
	movl -4(%rbp), %ebx
	int $0x80
	leave
	ret
