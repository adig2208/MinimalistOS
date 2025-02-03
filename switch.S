/*
 * file:        switch.s
 * description: assembly code to switch 64-bit stack
 * class:       CS 5600, 2025 SP
 */

/*
 * switch_to - save stack pointer to *location_for_old_sp, set 
 *             stack pointer to 'new_value', and return.
 *             Note that the return takes place on the new stack.
 *
 * switch_to(void **location_for_old_sp, void *new_value)
 *   location_for_old_sp = RDI
 *   new_value = RSI
 *
 * For more details, see:
 *  http://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf
 */
 
switch_to:
        /* frame pointer - makes life easier in assembler, too 
	 */
	push %rbp 
	mov  %rsp,%rbp
	
	/* debugging support - the last value pushed before switching
         * is a flag; check for that here and halt *before* switching
         * so you have a chance to debug
	 */ 
	mov  $0xA5A5A5A5A5A5A5A5,%rax
	cmp %rax, (%rsi)	/* flag value on top of new stack? */
	je   ok			/* yes - skip */
	mov  $0,%rax		/* no - simple assert */
	mov  0(%rax),%rax	
ok:	
	/* save and restore arg1 and arg2 so we can pass args to thread function
	*/
	push %rsi
	push %rdi
	
	/* C calling conventions require that we preserve %rbp (already
         * saved above), %rbx, %r12, $r13, %r14, %r15 - push them onto the stack
	*/
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15

	mov $0xA5A5A5A5A5A5A5A5, %rax
	push %rax		/* push the flag value */

	cmp  $0,%rdi		/* is 'location_for_old' null? */
	je   skip
	mov  %rsp,(%rdi)	/* into 'location_for_old' */
skip:
	
	mov %rsi,%rsp		/* switch */

	pop  %rax		/* pop flag and ignore it */

	pop %r15		/* pop callee-save registers */
	pop %r14
	pop %r13
	pop %r12
	pop %rbx
	
	pop %rdi		/* this is so we can pass args */
	pop %rsi

	pop %rbp		/* and the frame pointer */
	ret			/* and return */

.global	switch_to
