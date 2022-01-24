.text
.section .rodata
	.globl main
	.type main, @function
	.printnum:
		.string "%d\n"
		.text
	.lbp1:
		.string "Value variable:"
		.text
	.lbp2:
		.string "The code error will be:"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	movl $5, -4(%rbp)
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	leaq .lbp2(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
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
