/*
 * setup_stack2(stack, function, arg1, arg2) - sets up a stack so that
 * switching to it from 'switch_2' will call 'function' with arguments
 * 'arg1' and 'arg2'. Returns the resulting stack pointer.
 *
 */

void *setup_stack2(void *_stack, void *func, void *arg1, void *arg2)
{
    long *stack = _stack - ((long)_stack & 0x0F);
    long old_bp = (long)stack;	/* top frame - SP = BP */

    
    *(--stack) = 0x3A3A3A3A3A3A3A3A;    /* guard zone */
    *(--stack) = 0x3A3A3A3A3A3A3A3A;
    *(--stack) = 0x3A3A3A3A3A3A3A3A;

    /* this is the stack frame calling 'switch_to'
     */
    *(--stack) = (long)func;     /* return address */
    *(--stack) = old_bp;        /* %rbp */
    *(--stack) = (long)arg2;     /* argument */                 // RSI
    *(--stack) = (long)arg1;     /* argument (reverse order) */ // RDI 
    *(--stack) = 0;             /* %rbx */
    *(--stack) = 0;             /* %r12 */
    *(--stack) = 0;             /* %r13 */
    *(--stack) = 0;             /* %r14 */
    *(--stack) = 0;             /* %r15 */
    //    *(--stack) = 0;             /* %r15 */
    //    *(--stack) = 0;             /* %r15 */
    *(--stack) = 0xa5a5a5a5a5a5a5a5;    /* valid stack flag */

    return stack;
}

void *setup_stack1(void *_stack, void *func, void *arg1)
{
    return setup_stack2(_stack, func, arg1, 0);
}

void *setup_stack0(void *_stack, void *func)
{
    return setup_stack2(_stack, func, 0, 0);
}
