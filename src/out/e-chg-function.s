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
	.labl0:
		.string "First version: %d %c\n"
		.text
	.labl1:
		.string "Second version: %d %c\n"
		.text
	.labl2:
		.string "Third version: %d %c\n"
		.text
	.labl3:
		.string "Four version: %d %c\n"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	# < 1 > #
	subq $4, %rsp
	movl $65, -4(%rbp)
	# < 2 > #
	subq $4, %rsp
	movb $'A', -5(%rbp)
	# < 3 > #
	movl -4(%rbp), %esi
	movsbl -5(%rbp), %edx
	leaq .labl0(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 6 > #
	movl $66, -4(%rbp)
	# < 7 > #
	movb $'B', -5(%rbp)
	# < 8 > #
	movl -4(%rbp), %esi
	movsbl -5(%rbp), %edx
	leaq .labl1(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 11 > #
	subq $4, %rsp
	movl $67, -8(%rbp)
	# < 12 > #
	movl -8(%rbp), %eax
	movl %eax, -4(%rbp)
	# < 13 > #
	movzbl -8(%rbp), %eax
	movb %al, -5(%rbp)
	# < 14 > #
	movl -4(%rbp), %esi
	movsbl -5(%rbp), %edx
	leaq .labl2(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 17 > #
	subq $4, %rsp
	movb $'D', -9(%rbp)
	# < 18 > #
	movb -9(%rbp), %al
	movl %eax, -4(%rbp)
	# < 19 > #
	movb -9(%rbp), %al
	movb %al, -5(%rbp)
	# < 20 > #
	movl -4(%rbp), %esi
	movsbl -5(%rbp), %edx
	leaq .labl3(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 22 > #
	movq $60, %rax
	movq $0, %rdi
	syscall
	leave
	ret
