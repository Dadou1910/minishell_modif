#include "../includes/minishell.h"
int deal_out_pipe(t_command *cmd)
{
    if (cmd->fd_out != -1)
    {
        close(cmd->p[READ_END]);
        if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
            perror("dup2");
        close(cmd->fd_out);
    }
    else if (cmd->next != NULL && cmd->next->args[0] != NULL)
    {
        if (dup2(cmd->p[WRITE_END], STDOUT_FILENO) == -1)
            perror("dup2");
        close(cmd->p[WRITE_END]);
    }
    return 0;
}

int deal_in_pipe(t_command *cmd)
{
    if (cmd->fd_in != -1)
    {
        close(cmd->p[WRITE_END]);
        if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
            perror("dup2");
        close(cmd->fd_in);
    }
    else if (cmd->pprev != -1)
    {
        close(cmd->p[WRITE_END]);
        if (dup2(cmd->pprev, STDIN_FILENO) == -1)
            perror("dup2");
        close(cmd->pprev);
    }
    return 0;
}
