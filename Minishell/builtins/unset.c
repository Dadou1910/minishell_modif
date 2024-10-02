#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int count_env_vars(char **envp)
{
    int count = 0;
    while (envp[count] != NULL)
        count++;
    return count;
}

int unset(char ***envp, const char *var)
{
    int count = count_env_vars(*envp);
    char **new_env = malloc(sizeof(char *) * count);
    int i = 0;
    int j = 0;
    if (!new_env)
    {
        perror("malloc error");
        return(-1);
    }
    while (i < count)
    {
        if (strncmp((*envp)[i], var, strlen(var)) != 0 ||
            (*envp)[i][strlen(var)] != '=')
            new_env[j++] = (*envp)[i];
        i++;
    }
    new_env[j] = NULL;
    free(*envp);
    *envp = new_env;
    return(0);
}
