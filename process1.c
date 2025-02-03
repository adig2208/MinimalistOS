/*
 * micro-program - process 1 task switch program
 */

extern void  print(char *s);
extern char *getarg(int i);
extern void  yield12(void);
extern void  yield21(void);
extern void  uexit(void);

int main(int c)
{
    print("program 1\n");
    yield12();

    print("program 1\n");
    yield12();

    print("program 1\n");
    yield12();

    print("program 1\n");
    yield12();
    uexit();

    return 0;
}
