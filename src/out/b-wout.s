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
		.string "I don't know what think about that"
		.text
	.labl1:
		.string "Maybe it's better..."
		.text
	.labl2:
		.string "I deleted all C++ files, a big mistake"
		.text
	.labl3:
		.string "Coding again all C++ files"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	# < 1 > #
	leaq .labl0(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	# < 2 > #
	leaq .labl1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	# < 3 > #
	leaq .labl2(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	# < 4 > #
	leaq .labl3(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	# < 6 > #
	movq $60, %rax
	movq $0, %rdi
	syscall
	leave
	ret
