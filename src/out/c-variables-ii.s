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
	# < 1 > #
	subq $4, %rsp
	movb $'j', -1(%rbp)
	# < 2 > #
	subq $4, %rsp
	movl $106, -8(%rbp)
	# < 4 > #
	subq $4, %rsp
	movl -8(%rbp), %eax
	movb %al, -9(%rbp)
	# < 5 > #
	subq $4, %rsp
	movsbl -1(%rbp), %eax
	movl %eax, -16(%rbp)
	# < 7 > #
	subq $4, %rsp
	movl - 16(%rbp), %eax
	movl %eax, -20(%rbp)
	# < 8 > #
	subq $4, %rsp
	movzbl -9(%rbp), %eax
	movb %al, -21(%rbp)
	# < 10 > #
	movsbl -1(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 11 > #
	movl -8(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 12 > #
	movsbl -9(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 13 > #
	movl -16(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 14 > #
	movsbl -21(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 15 > #
	movl -20(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 17 > #
	subq $4, %rsp
	movl $-16, -24(%rbp)
	# < 18 > #
	subq $4, %rsp
	movb $'s', -25(%rbp)
	# < 19 > #
	movl -24(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 20 > #
	movsbl -25(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 22 > #
	movq $60, %rax
	movq $0, %rdi
	syscall
	leave
	ret
