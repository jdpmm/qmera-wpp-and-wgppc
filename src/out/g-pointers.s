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
	.printadrs:
		.string "%p\n"
		.text
	.labl0:
		.string "Value variable: %d\n"
		.text
	.labl1:
		.string "Value variable from the pointer: %d\n"
		.text
	.labl2:
		.string "Variable's address: %p\n"
		.text
	.labl3:
		.string "Pointer's address: %p\n"
		.text
	.labl4:
		.string "VALUE: %d %d %d %d %d %d %d %d %d\n"
		.text
	.labl5:
		.string "ADDRESS: %p %p %p %p %p %p %p %p\n"
		.text
main:
	pushq %rbp
	movq %rsp, %rbp
	# < 6 > #
	subq    $4, %rsp
	movl    $16, -4(%rbp)
	# < 7 > #
	subq    $4, %rsp
	movl    -4(%rbp), %r15d
	leaq    -8(%rbp), %rax
	movq    %rax, -4(%rbp)
	movl    %r15d, -8(%rbp)
	movl    $0, %r15d
	# < 9 > #
	movl    -8(%rbp), %esi
	leaq    .labl0(%rip), %rdi
	movl    $0, %eax
	call    printf@PLT
	movl    $0, %eax
	# < 10 > #
	movq    -4(%rbp), %rax
	movl    (%rax), %esi
	leaq    .labl1(%rip), %rdi
	movl    $0, %eax
	call    printf@PLT
	movl    $0, %eax
	# < 11 > #
	leaq -8(%rbp), %rax
	movq %rax, %rsi
	leaq    .labl2(%rip), %rdi
	movl    $0, %eax
	call    printf@PLT
	movl    $0, %eax
	# < 12 > #
	leaq -4(%rbp), %rax
	movq %rax, %rsi
	leaq    .labl3(%rip), %rdi
	movl    $0, %eax
	call    printf@PLT
	movl    $0, %eax
	# < 14 > #
	movq    -4(%rbp), %rax
	movl    (%rax), %esi
	movq    -4(%rbp), %rax
	movl    (%rax), %edx
	movq    -4(%rbp), %rax
	movl    (%rax), %ecx
	movq    -4(%rbp), %rax
	movl    (%rax), %r8d
	movq    -4(%rbp), %rax
	movl    (%rax), %r9d
	subq    $8, %rsp
	movq    -4(%rbp), %rax
	pushq   (%rax)
	movq    -4(%rbp), %rax
	pushq   (%rax)
	movq    -4(%rbp), %rax
	pushq   (%rax)
	movq    -4(%rbp), %rax
	pushq   (%rax)
	leaq    .labl4(%rip), %rdi
	movl    $0, %eax
	call    printf@PLT
	movl    $0, %eax
	addq    $8, %rsp
	# < 15 > #
	leaq -8(%rbp), %rax
	movq %rax, %rsi
	leaq -8(%rbp), %rax
	movq %rax, %rdx
	leaq -8(%rbp), %rax
	movq %rax, %rcx
	leaq -8(%rbp), %rax
	movq %rax, %r8
	leaq -8(%rbp), %rax
	movq %rax, %r9
	subq    $8, %rsp
	movl    -8(%rbp), %eax
	pushq   %rax
	leaq   -8(%rbp), %rax
	pushq  %rax
	movl    -8(%rbp), %eax
	pushq   %rax
	leaq   -8(%rbp), %rax
	pushq  %rax
	movl    -8(%rbp), %eax
	pushq   %rax
	leaq   -8(%rbp), %rax
	pushq  %rax
	leaq    .labl5(%rip), %rdi
	movl    $0, %eax
	call    printf@PLT
	movl    $0, %eax
	addq    $8, %rsp
	# < 17 > #
	movq    $60, %rax
	movq    $0, %rdi
	syscall
	leave
	ret
