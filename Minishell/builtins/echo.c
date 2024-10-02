#include "../includes/minishell.h"

int echo(char **args)
{
    int newline = 1;
    int i = 1;

    if (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        i++;
        if (args[i])
            printf(" ");
    }
    if (newline)
        printf("\n");
    return(0);
}
