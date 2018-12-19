#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
/*
hook strcmp，so typedef了一个STRCMP函数pointer
hook的目的是要控制函数action，从libc.so.6中拿到strcmp's pointer，保存成old_strcmp
*/

typedef int(*STRCMP)(const char*, const char*);

int strcmp(const char *s1, const char *s2)
{
    printf("------> Because run as: LD_PRELOAD=./invoke.so ./tt, the invoke.so will be loaded first, so\n \
            invoke.so's strcmp will be called to replace libso.strcmp.\n");
    static void *handle = NULL;
    static STRCMP old_strcmp = NULL;
    int iRet = -1;

    if( !handle )
    {
        handle = dlopen("libc.so.6", RTLD_LAZY);
        old_strcmp = (STRCMP)dlsym(handle, "strcmp");
        printf("------> first do invoke.so's  strcmp, print strcmp parameters: s1=<%s> s2=<%s>, \n \
                then call libc.so's strcmp\n", s1, s2);
        iRet = old_strcmp(s1, s2);
        printf("------> [old_strcmp(s1, s2)]=[%d]\n", iRet);
    }
    printf("\n");

    return iRet;
}
