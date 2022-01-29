.text
.section .rodata
	.globl main
	.type main, @function
	.printnum:
		.string "%d\n"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $0, %r14d
	movl $4, %r14d
	addl $4, %r14d
	subq $4, %rsp
	movl %r14d, -4(%rbp)
	movl $0, %r14d
	movl -4(%rbp), %r14d
	subl $3, %r14d
	subq $4, %rsp
	movl %r14d, -8(%rbp)
	movl $0, %r14d
	movl -4(%rbp), %r14d
	imull -8(%rbp), %r14d
	subq $4, %rsp
	movl %r14d, -12(%rbp)
	movl $0, %r14d
	movl -12(%rbp), %r14d
	movl $0, %edx
	movl %r14d, %eax
	movl $5, %ecx
	idiv %ecx
	movl %eax, %r14d
	subq $4, %rsp
	movl %r14d, -16(%rbp)
	movl $0, %r14d
	movl $4, %r14d
	movl $0, %edx
	movl %r14d, %eax
	movl $2, %ecx
	idiv %ecx
	movl %edx, %r14d
	subq $4, %rsp
	movl %r14d, -20(%rbp)
	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl -8(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl -12(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl -16(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl -20(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $0, %r14d
	movl -4(%rbp), %r14d
	addl -8(%rbp), %r14d
	addl -12(%rbp), %r14d
	addl -16(%rbp), %r14d
	addl -20(%rbp), %r14d
	movl %r14d, %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $0, %r14d
	movl -4(%rbp), %r14d
	subl -8(%rbp), %r14d
	subl -12(%rbp), %r14d
	subl -16(%rbp), %r14d
	subl -20(%rbp), %r14d
	movl $1, %eax
	movl %r14d, %ebx
	int $0x80
	leave
	ret
