#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("argc=[%d]\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d]=[%s]\n", i, argv[i]);
    }
    printf("will call libc's strcmp\n\n");

    int iCmp = strcmp(argv[0], "test");
    printf("[%d]=[strcmp(%s, \"test\");]\n", iCmp, argv[0]);

    if (iCmp == 0)
    {
        printf("process named test.\n");
    }
    else
    {
        printf("process not named test.\n");
    }

    return 0;
}
