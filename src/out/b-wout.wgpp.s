.text
.section .rodata
	.globl main
	.type main, @function
	.printnum:
		.string "%d"
		.text
	.lbp1:
		.string "hola como estas"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	movl $1, %eax
	movl $0, %ebx
	int $0x80
	leave
	ret
