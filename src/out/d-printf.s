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
		.string "Patron: %d%d%d\n\t- %c%c%c%c%c\n%d\n"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	# < 1 > #
	subq $4, %rsp
	movl $3, -4(%rbp)
	# < 2 > #
	subq $4, %rsp
	movl $6, -8(%rbp)
	# < 3 > #
	subq $4, %rsp
	movl $9, -12(%rbp)
	# < 4 > #
	subq $4, %rsp
	movb $'j', -13(%rbp)
	# < 5 > #
	subq $4, %rsp
	movb $'d', -14(%rbp)
	# < 6 > #
	subq $4, %rsp
	movb $'p', -15(%rbp)
	# < 7 > #
	subq $4, %rsp
	movb $'m', -16(%rbp)
	# < 9 > #
	movl -4(%rbp), %esi
	movl -8(%rbp), %edx
	movl -12(%rbp), %ecx
	movsbl -13(%rbp), %r8d
	movsbl -14(%rbp), %r9d
	subq $8, %rsp
	movl -4(%rbp), %eax
	pushq %rax
	movsbl -16(%rbp), %eax
	pushq %rax
	movsbl -16(%rbp), %eax
	pushq %rax
	movsbl -15(%rbp), %eax
	pushq %rax
	leaq .labl0(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	addq $8, %rsp
	# < 11 > #
	subq $4, %rsp
	movl $16, -8(%rbp)
	# < 12 > #
	movl -8(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 14 > #
	movq $60, %rax
	movq $0, %rdi
	syscall
	leave
	ret
