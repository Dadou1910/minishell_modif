#include "../includes/minishell.h"

int execute_cmd(t_command *cmd)
{
    if (pipe(cmd->p) == -1)
        perror("pipe");

    cmd->table->pids[cmd->table->ipids] = fork();
    if (cmd->table->pids[cmd->table->ipids] == 0)
    {
        cmd->table->ipids++;
        deal_in_pipe(cmd);
        deal_out_pipe(cmd);
        execute(cmd);
        perror("execute");
    }
    else if (cmd->table->pids[cmd->table->ipids] < 0)
    {
        perror("fork");
    }
    close(cmd->p[WRITE_END]);
    if (cmd->next != NULL)
        cmd->next->pprev = cmd->p[READ_END];
    else
        close(cmd->p[READ_END]);
    return 0;
}
