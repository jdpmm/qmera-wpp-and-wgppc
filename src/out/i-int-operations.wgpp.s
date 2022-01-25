.text
.section .rodata
	.globl main
	.type main, @function
	.printnum:
		.string "%d\n"
		.text
	.lbp1:
		.string "Original value. %d\n"
		.text
	.lbp2:
		.string "INC operation: %d\n"
		.text
	.lbp3:
		.string "DEC operation: %d\n"
		.text
	.lbp4:
		.string "NEG opration %d\n"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	movl $3, -4(%rbp)
	movl -4(%rbp), %esi
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	incl -4(%rbp)
	movl -4(%rbp), %esi
	leaq .lbp2(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	decl -4(%rbp)
	movl -4(%rbp), %esi
	leaq .lbp3(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	negl -4(%rbp)
	movl -4(%rbp), %esi
	leaq .lbp4(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $1, %eax
	movl $0, %ebx
	int $0x80
	leave
	ret
