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
		.string "Initial value: %d\n"
		.text
	.labl1:
		.string "INC fucntion called twice %d\n"
		.text
	.labl2:
		.string "DEC fucntion called once %d\n"
		.text
	.labl3:
		.string "NEG fucntion called %d\n"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	# < 1 > #
	subq $4, %rsp
	movl $0, -4(%rbp)
	# < 2 > #
	movl -4(%rbp), %esi
	leaq .labl0(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 4 > #
	incl -4(%rbp)
	# < 5 > #
	incl -4(%rbp)
	# < 6 > #
	movl -4(%rbp), %esi
	leaq .labl1(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 8 > #
	decl -4(%rbp)
	# < 9 > #
	movl -4(%rbp), %esi
	leaq .labl2(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 11 > #
	negl -4(%rbp)
	# < 12 > #
	movl -4(%rbp), %esi
	leaq .labl3(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	# < 14 > #
	movq $60, %rax
	movq $0, %rdi
	syscall
	leave
	ret
