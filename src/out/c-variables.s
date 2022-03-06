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
	movb $'d', -2(%rbp)
	# < 3 > #
	subq $4, %rsp
	movb $'p', -3(%rbp)
	# < 4 > #
	subq $4, %rsp
	movb $'m', -4(%rbp)
	# < 5 > #
	subq $4, %rsp
	movb $'m', -5(%rbp)
	# < 6 > #
	subq $4, %rsp
	movb $'1', -6(%rbp)
	# < 7 > #
	subq $4, %rsp
	movb $'6', -7(%rbp)
	# < 8 > #
	subq $4, %rsp
	movb $'6', -8(%rbp)
	# < 9 > #
	subq $4, %rsp
	movb $'9', -9(%rbp)
	# < 10 > #
	subq $4, %rsp
	movl $16, -16(%rbp)
	# < 12 > #
	subq $4, %rsp
	movb $'0', -17(%rbp)
	# < 13 > #
	subq $4, %rsp
	movl $-16, -24(%rbp)
	# < 15 > #
	movsbl -1(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 16 > #
	movsbl -2(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 17 > #
	movsbl -3(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 18 > #
	movsbl -4(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 19 > #
	movsbl -5(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 20 > #
	movsbl -6(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 21 > #
	movsbl -7(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 22 > #
	movsbl -8(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 23 > #
	movsbl -9(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 24 > #
	movl -16(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 25 > #
	movsbl -17(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 26 > #
	movl -24(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 28 > #
	subq $4, %rsp
	movb $'\n', -25(%rbp)
	# < 29 > #
	movq $60, %rax
	movsbq -25(%rbp), %rdi
	syscall
	leave
	ret
