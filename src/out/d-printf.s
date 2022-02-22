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
		.string "Patron: %d %d %d\n\t- %cdpmm\n"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	movl $3, -4(%rbp)
	subq $4, %rsp
	movl $6, -8(%rbp)
	subq $4, %rsp
	movl $9, -12(%rbp)
	subq $4, %rsp
	movb $'j', -13(%rbp)
	movl -4(%rbp), %esi
	movl -8(%rbp), %edx
	movl -12(%rbp), %ecx
	movsbl -13(%rbp), %r8d
	leaq .labl0(%rip), %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movq $60, %rax
	movq $0, %rdi
	syscall
	leave
	ret
