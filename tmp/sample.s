	.text
	.file	"sample_source_code_plus.cpp"
	.globl	_Z4off1i                        # -- Begin function _Z4off1i
	.p2align	4, 0x90
	.type	_Z4off1i,@function
_Z4off1i:                               # @_Z4off1i
	.cfi_startproc
# %bb.0:                                # %entry
	movl	$5, %eax
	subl	%edi, %eax
	retq
.Lfunc_end0:
	.size	_Z4off1i, .Lfunc_end0-_Z4off1i
	.cfi_endproc
                                        # -- End function
	.globl	_Z6divideii                     # -- Begin function _Z6divideii
	.p2align	4, 0x90
	.type	_Z6divideii,@function
_Z6divideii:                            # @_Z6divideii
	.cfi_startproc
# %bb.0:                                # %entry
                                        # kill: def $esi killed $esi def $rsi
	movl	%edi, %eax
	cltd
	idivl	%esi
                                        # kill: def $eax killed $eax def $rax
	addl	%esi, %eax
	addl	$2, %eax
	retq
.Lfunc_end1:
	.size	_Z6divideii, .Lfunc_end1-_Z6divideii
	.cfi_endproc
                                        # -- End function
	.globl	_Z7subdiveiis                   # -- Begin function _Z7subdiveiis
	.p2align	4, 0x90
	.type	_Z7subdiveiis,@function
_Z7subdiveiis:                          # @_Z7subdiveiis
	.cfi_startproc
# %bb.0:                                # %entry
	movl	%edx, %ecx
	movl	%edi, %eax
	cltd
	idivl	%esi
	subl	%ecx, %eax
	addl	$1, %eax
	retq
.Lfunc_end2:
	.size	_Z7subdiveiis, .Lfunc_end2-_Z7subdiveiis
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$_ZSt4cout, %edi
	movl	$-24, %esi
	callq	_ZNSolsEi
	movl	$.L.str, %esi
	movl	$1, %edx
	movq	%rax, %rdi
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$_ZSt4cout, %edi
	movl	$12, %esi
	callq	_ZNSolsEi
	movl	$.L.str, %esi
	movl	$1, %edx
	movq	%rax, %rdi
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$_ZSt4cout, %edi
	movl	$5, %esi
	callq	_ZNSolsEi
	movl	$.L.str, %esi
	movl	$1, %edx
	movq	%rax, %rdi
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end3:
	.size	main, .Lfunc_end3-main
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90                         # -- Begin function _GLOBAL__sub_I_sample_source_code_plus.cpp
	.type	_GLOBAL__sub_I_sample_source_code_plus.cpp,@function
_GLOBAL__sub_I_sample_source_code_plus.cpp: # @_GLOBAL__sub_I_sample_source_code_plus.cpp
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	callq	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	movl	$_ZStL8__ioinit, %esi
	movl	$__dso_handle, %edx
	callq	__cxa_atexit
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end4:
	.size	_GLOBAL__sub_I_sample_source_code_plus.cpp, .Lfunc_end4-_GLOBAL__sub_I_sample_source_code_plus.cpp
	.cfi_endproc
                                        # -- End function
	.type	_ZStL8__ioinit,@object          # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"\n"
	.size	.L.str, 2

	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_sample_source_code_plus.cpp
	.ident	"clang version 13.0.1 (https://github.com/llvm/llvm-project.git 73daeb3d507f7c8da52a35311ec1799f161ac7a5)"
	.section	".note.GNU-stack","",@progbits
