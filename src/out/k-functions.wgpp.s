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
		.string "Hey from one function"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	call namefunction
	call namefunction
	call namefunction
	call namefunction
	call namefunction
	call namefunction
	call namefunction
	call namefunction
	call namefunction
	movl $1, %eax
	movl $0, %ebx
	int $0x80
	leave
	ret
namefunction:
	pushq %rbp
	movq %rsp, %rbp
	leaq .lbp1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax
	leave
	ret
