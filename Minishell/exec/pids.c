#include "../includes/minishell.h"

void wait_pids(t_command *cmd)
{
    int i = 0;
    while (i < cmd->table->ipids)
    {
        wait(&cmd->table->pids[i]);
        i++;
    }
    free(cmd->table->pids);
}


int launch(t_command *cmd)
{
    while(cmd && cmd->args[0])
    {
        // if(is_builtins(cmd) == -1)
        //     execute(cmd);
        cmd->table->ipids++;
        cmd = cmd->next;
    }
    wait_pids(cmd);
    return(1);
}
