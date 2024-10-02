#include "../includes/minishell.h"

int is_builtins(t_command *cmd)
{
    if(strcmp(cmd->args[0], "echo") == 0)
        return(echo(cmd->args));
    else if(strcmp(cmd->args[0], "cd") == 0)
        return(cd(cmd->args));
    else if(strcmp(cmd->args[0], "pwd") == 0)
        return(pwd());
    else if(strcmp(cmd->args[0], "env") == 0)
        return(env(cmd->table->envp));
    else if(strcmp(cmd->args[0], "unset") == 0)
        return(unset(cmd->table->envp, cmd->args[1]));
    return(-1);
}