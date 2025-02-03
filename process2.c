/*
 * micro-program - process 1 task switch program
 */

extern void  print(char *s);
extern void  yield12(void);
extern void  yield21(void);
extern void  uexit(void);

int main(void)
{
    print("program 2\n");
    yield21();

    print("program 2\n");
    yield21();

    print("program 2\n");
    yield21();

    print("program 2\n");
    yield21();

    uexit();

    return 0;
}
