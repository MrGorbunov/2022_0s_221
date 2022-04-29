	.file	"sumArray.c"
# GNU C99 (Ubuntu 7.5.0-3ubuntu1~18.04) version 7.5.0 (x86_64-linux-gnu)
#	compiled by GNU C version 7.5.0, GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0, isl version isl-0.19-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu sumArray.c -mtune=generic
# -march=x86-64 -auxbase-strip sumArray.s -Og -Wall -Werror -std=c99
# -fverbose-asm -fstack-protector-strong -Wformat-security
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -fasynchronous-unwind-tables -fauto-inc-dec -fchkp-check-incomplete-type
# -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
# -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
# -fchkp-use-static-bounds -fchkp-use-static-const-bounds
# -fchkp-use-wrappers -fcombine-stack-adjustments -fcommon -fcompare-elim
# -fcprop-registers -fdefer-pop -fdelete-null-pointer-checks
# -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
# -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse-lm
# -fgnu-runtime -fgnu-unique -fguess-branch-probability -fident -finline
# -finline-atomics -fipa-profile -fipa-pure-const -fipa-reference
# -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
# -fivopts -fkeep-static-consts -fleading-underscore -flifetime-dse
# -flto-odr-type-merging -fmath-errno -fmerge-constants
# -fmerge-debug-strings -fomit-frame-pointer -fpeephole -fplt
# -fprefetch-loop-arrays -freg-struct-return -freorder-blocks
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
# -fshow-column -fshrink-wrap -fshrink-wrap-separate -fsigned-zeros
# -fsplit-ivs-in-unroller -fsplit-wide-types -fssa-backprop
# -fstack-protector-strong -fstdarg-opt -fstrict-volatile-bitfields
# -fsync-libcalls -ftoplevel-reorder -ftrapping-math
# -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
# -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
# -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-if-convert
# -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
# -ftree-parallelize-loops= -ftree-phiprop -ftree-reassoc -ftree-scev-cprop
# -ftree-sink -ftree-slsr -ftree-ter -funit-at-a-time -funwind-tables
# -fverbose-asm -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -malign-stringops -mavx256-split-unaligned-load
# -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387 -mfxsr
# -mglibc -mieee-fp -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone
# -msse -msse2 -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
	.globl	sumArrayRows
	.type	sumArrayRows, @function
sumArrayRows:
.LFB23:
	.cfi_startproc
# sumArray.c:22:     MARKER_START = 211;
	movb	$-45, MARKER_START(%rip)	#, MARKER_START
# sumArray.c:23:     for ( int i=0; i<M; i++ )
	movl	$0, %r8d	#, i
# sumArray.c:20:     short sum = 0;
	movl	$0, %eax	#, <retval>
# sumArray.c:23:     for ( int i=0; i<M; i++ )
	jmp	.L2	#
.L3:
# sumArray.c:26:             sum += a[i][j];
	movslq	%r8d, %rdx	# i, i
	salq	$4, %rdx	#, tmp99
	addq	%rdi, %rdx	# a, _3
	movslq	%ecx, %rsi	# j, j
	addw	(%rdx,%rsi,2), %ax	# *_3, <retval>
# sumArray.c:24:         for ( int j=0; j<N; j++ ) {
	addl	$1, %ecx	#, j
.L4:
# sumArray.c:24:         for ( int j=0; j<N; j++ ) {
	cmpl	$7, %ecx	#, j
	jle	.L3	#,
# sumArray.c:23:     for ( int i=0; i<M; i++ )
	addl	$1, %r8d	#, i
.L2:
# sumArray.c:23:     for ( int i=0; i<M; i++ )
	cmpl	$1, %r8d	#, i
	jg	.L6	#,
# sumArray.c:24:         for ( int j=0; j<N; j++ ) {
	movl	$0, %ecx	#, j
	jmp	.L4	#
.L6:
# sumArray.c:28:     MARKER_END = 211;
	movb	$-45, MARKER_END(%rip)	#, MARKER_END
# sumArray.c:32: }
	ret
	.cfi_endproc
.LFE23:
	.size	sumArrayRows, .-sumArrayRows
	.globl	sumArrayCols
	.type	sumArrayCols, @function
sumArrayCols:
.LFB24:
	.cfi_startproc
# sumArray.c:39:     MARKER_START = 211;
	movb	$-45, MARKER_START(%rip)	#, MARKER_START
# sumArray.c:40:     for ( int j=0; j<N; j++ )
	movl	$0, %esi	#, j
# sumArray.c:37:     short sum = 0;
	movl	$0, %eax	#, <retval>
# sumArray.c:40:     for ( int j=0; j<N; j++ )
	jmp	.L8	#
.L9:
# sumArray.c:42:             sum += a[i][j];
	movslq	%ecx, %rdx	# i, i
	salq	$4, %rdx	#, tmp99
	addq	%rdi, %rdx	# a, _3
	movslq	%esi, %r8	# j, j
	addw	(%rdx,%r8,2), %ax	# *_3, <retval>
# sumArray.c:41:         for ( int i=0; i<M; i++ )
	addl	$1, %ecx	#, i
.L10:
# sumArray.c:41:         for ( int i=0; i<M; i++ )
	cmpl	$1, %ecx	#, i
	jle	.L9	#,
# sumArray.c:40:     for ( int j=0; j<N; j++ )
	addl	$1, %esi	#, j
.L8:
# sumArray.c:40:     for ( int j=0; j<N; j++ )
	cmpl	$7, %esi	#, j
	jg	.L12	#,
# sumArray.c:41:         for ( int i=0; i<M; i++ )
	movl	$0, %ecx	#, i
	jmp	.L10	#
.L12:
# sumArray.c:43:     MARKER_END = 211;
	movb	$-45, MARKER_END(%rip)	#, MARKER_END
# sumArray.c:47: }
	ret
	.cfi_endproc
.LFE24:
	.size	sumArrayCols, .-sumArrayCols
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"w"
.LC1:
	.string	".marker"
.LC2:
	.string	"sumArray.c"
.LC3:
	.string	"marker_fp"
.LC4:
	.string	"%llx\n%llx"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC6:
	.string	"sumArrayRows took %lf seconds.\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx	#
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$72, %rsp	#,
	.cfi_def_cfa_offset 96
# sumArray.c:50: {
	movq	%fs:40, %rax	#, tmp118
	movq	%rax, 56(%rsp)	# tmp118, D.2498
	xorl	%eax, %eax	# tmp118
# sumArray.c:54:     srand((unsigned) time(&t));
	leaq	8(%rsp), %rdi	#, tmp105
	call	time@PLT	#
	movl	%eax, %edi	# _1,
	call	srand@PLT	#
# sumArray.c:61:     FILE* marker_fp = fopen(".marker","w");
	leaq	.LC0(%rip), %rsi	#,
	leaq	.LC1(%rip), %rdi	#,
	call	fopen@PLT	#
# sumArray.c:62:     assert(marker_fp);
	testq	%rax, %rax	# marker_fp
	je	.L21	#,
	movq	%rax, %rbx	#, marker_fp
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:97:   return __fprintf_chk (__stream, __USE_FORTIFY_LEVEL - 1, __fmt,
	leaq	MARKER_END(%rip), %r8	#,
	leaq	MARKER_START(%rip), %rcx	#,
	leaq	.LC4(%rip), %rdx	#,
	movl	$1, %esi	#,
	movq	%rax, %rdi	# marker_fp,
	movl	$0, %eax	#,
	call	__fprintf_chk@PLT	#
# sumArray.c:66:     fclose(marker_fp);
	movq	%rbx, %rdi	# marker_fp,
	call	fclose@PLT	#
# sumArray.c:70:     for ( int j=0; j<N; j++ )
	movl	$0, %ebp	#, j
	jmp	.L15	#
.L21:
# sumArray.c:62:     assert(marker_fp);
	leaq	__PRETTY_FUNCTION__.2460(%rip), %rcx	#,
	movl	$62, %edx	#,
	leaq	.LC2(%rip), %rsi	#,
	leaq	.LC3(%rip), %rdi	#,
	call	__assert_fail@PLT	#
.L16:
# sumArray.c:72:             a[i][j] = rand() % 256;
	call	rand@PLT	#
	cltd
	shrl	$24, %edx	#, tmp107
	addl	%edx, %eax	# tmp107, tmp108
	movzbl	%al, %eax	# tmp108, tmp109
	subl	%edx, %eax	# tmp107, tmp110
	movslq	%ebp, %rdx	# j, j
	movslq	%ebx, %rcx	# i, i
	leaq	(%rdx,%rcx,8), %rdx	#, tmp114
	movw	%ax, 16(%rsp,%rdx,2)	# tmp110, a
# sumArray.c:71:         for ( int i=0; i<M; i++ )
	addl	$1, %ebx	#, i
.L17:
# sumArray.c:71:         for ( int i=0; i<M; i++ )
	cmpl	$1, %ebx	#, i
	jle	.L16	#,
# sumArray.c:70:     for ( int j=0; j<N; j++ )
	addl	$1, %ebp	#, j
.L15:
# sumArray.c:70:     for ( int j=0; j<N; j++ )
	cmpl	$7, %ebp	#, j
	jg	.L22	#,
# sumArray.c:71:         for ( int i=0; i<M; i++ )
	movl	$0, %ebx	#, i
	jmp	.L17	#
.L22:
# sumArray.c:82:     start = clock();
	call	clock@PLT	#
	movq	%rax, %rbx	#, start
# sumArray.c:83:     sumArrayRows(a);
	leaq	16(%rsp), %rdi	#, tmp115
	call	sumArrayRows	#
# sumArray.c:84:     end = clock();
	call	clock@PLT	#
# sumArray.c:85:     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	subq	%rbx, %rax	# start, _8
	pxor	%xmm0, %xmm0	# _9
	cvtsi2sdq	%rax, %xmm0	# _8, _9
	divsd	.LC5(%rip), %xmm0	#, cpu_time_used
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:104:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC6(%rip), %rsi	#,
	movl	$1, %edi	#,
	movl	$1, %eax	#,
	call	__printf_chk@PLT	#
# sumArray.c:90:     exit(EXIT_SUCCESS);
	movl	$0, %edi	#,
	call	exit@PLT	#
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.2460, @object
	.size	__PRETTY_FUNCTION__.2460, 5
__PRETTY_FUNCTION__.2460:
	.string	"main"
	.comm	MARKER_END,1,1
	.comm	MARKER_START,1,1
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC5:
	.long	0
	.long	1093567616
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
