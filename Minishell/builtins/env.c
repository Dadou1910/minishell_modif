#include "../includes/minishell.h"

int env(char **envp)
{
    int i = 0;

    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return(0);
}
