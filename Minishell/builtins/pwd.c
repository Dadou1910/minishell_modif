#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    return(0);
}

