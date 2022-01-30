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
	.lbp1:
		.string "%d is equals to %c in ascii code\n"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	movb $'b', -1(%rbp)
	subq $4, %rsp
	movl $98, -8(%rbp)
	movl -8(%rbp), %esi
	movsbl -1(%rbp), %edx
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	subq $4, %rsp
	movb -1(%rbp), %al
	movb %al, -9(%rbp)
	subq $4, %rsp
	movl -1(%rbp), %eax
	movl %eax, -16(%rbp)
	movl -9(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl -16(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movb $'j', -9(%rbp)
	movb -9(%rbp), %al
	movb %al, -16(%rbp)
	movl -9(%rbp), %eax
	movl %eax, %esi
	leaq .printchr(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl -16(%rbp), %eax
	movl %eax, %esi
	leaq .printnum(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $1, %eax
	movl $0, %ebx
	int $0x80
	leave
	ret
