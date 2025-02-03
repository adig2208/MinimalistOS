/* Copyright (C) 2001-2024 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
	
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
	

/* This is a stripped-down version of the x86_64 syscall function
 * from the GNU C Library. 
 */
	/* start of the code section */
	.text 			
	/* define syscall as a global (exported) function */
	.globl	syscall;
	.type 	syscall,@function;
	.align	16

/* label for the entry point of the function */
syscall:
 	/* arg0: rdi, 
	 * arg1: rsi, 
	 * arg2: rdx, 
	 * arg3: rcx, 
	 * arg4: r8, 
 	 * arg5: r9 
	 * arg6: 8(%rsp)
         */
	movq %rdi, %rax		/* Syscall number -> rax.  */
	movq %rsi, %rdi		/* shift arg1 - arg5.  */
	movq %rdx, %rsi
	movq %rcx, %rdx
	movq %r8, %r10
	movq %r9, %r8
	movq 8(%rsp),%r9	/* arg6 is on the stack.  */
	syscall			/* Do the system call.  */
	cmpq $-4095, %rax	/* Check %rax for error.  */
	jae _syscall_error	/* Jump to error handler if error.  */
	ret			/* Return to caller.  */
_syscall_error:
	or $-1, %rax            /* Return -1 */
	ret
	
