	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_add
	.align	4, 0x90
_add:                                   ## @add
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	movss	%xmm0, -4(%rbp)
	movss	%xmm1, -8(%rbp)
	movss	-4(%rbp), %xmm0         ## xmm0 = mem[0],zero,zero,zero
	addss	-8(%rbp), %xmm0
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__literal8,8byte_literals
	.align	3
LCPI1_0:
	.quad	4613937818241073152     ## double 3
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_add_and_multiply
	.align	4, 0x90
_add_and_multiply:                      ## @add_and_multiply
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movss	%xmm0, -4(%rbp)
	movss	%xmm1, -8(%rbp)
	movss	-4(%rbp), %xmm0         ## xmm0 = mem[0],zero,zero,zero
	movss	-8(%rbp), %xmm1         ## xmm1 = mem[0],zero,zero,zero
	callq	_add
	movsd	LCPI1_0(%rip), %xmm1    ## xmm1 = mem[0],zero
	movss	%xmm0, -12(%rbp)
	cvtss2sd	-12(%rbp), %xmm0
	mulsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-12(%rbp), %xmm0        ## xmm0 = mem[0],zero,zero,zero
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_nCompletionStatus      ## @nCompletionStatus
.zerofill __DATA,__common,_nCompletionStatus,4,2

.subsections_via_symbols
