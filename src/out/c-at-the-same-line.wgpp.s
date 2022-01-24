.text
.section .rodata
	.globl main
	.type main, @function
	.printnum:
		.string "%d"
		.text
	.lbp1:
		.string "line 1"
		.text
	.lbp2:
		.string "line 1 as well"
		.text
	.lbp3:
		.string "Good bye :D"
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
	leaq .lbp2(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	leaq .lbp3(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	movl $1, %eax
	movl $0, %ebx
	int $0x80
	leave
	ret
