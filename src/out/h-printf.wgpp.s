.text
.section .rodata
	.globl main
	.type main, @function
	.printnum:
		.string "%d\n"
		.text
	.lbp1:
		.string "values: %d %d %d %d %d\n"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	movl $1, -4(%rbp)
	subq $4, %rsp
	movl $2, -8(%rbp)
	subq $4, %rsp
	movl $3, -12(%rbp)
	subq $4, %rsp
	movl $4, -16(%rbp)
	subq $4, %rsp
	movl $5, -20(%rbp)
	movl -4(%rbp), %esi
	movl -8(%rbp), %edx
	movl -12(%rbp), %ecx
	movl -16(%rbp), %r8d
	movl -20(%rbp), %r9d
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $1, %eax
	movl $0, %ebx
	int $0x80
	leave
	ret
