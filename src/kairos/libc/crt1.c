extern void __kairos_call_ctors(void);
extern int main(int, char *[]);
extern void __prepare_for_exit(void);
void _Exit(int) __attribute__((noreturn));

void _start(void)
{
    __kairos_call_ctors();

    int r = main(0, 0);

    __prepare_for_exit();

    if (r != 0)
    {
        _Exit(r);
    }
}