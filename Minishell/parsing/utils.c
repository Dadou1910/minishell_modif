/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeannelefevre <jeannelefevre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/10/01 13:09:03 by jeannelefev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    initialize_t_command(t_command *cmd)
{
    cmd->args = NULL;
    cmd->fd_in = -1;
    cmd->fd_out = -1;
    cmd->p = NULL;
    cmd->pprev = -1;
    cmd->pipe_count = 0;
    cmd->next = NULL;
}

void initialize_t_main(t_table *table, char **envp)
{
    table->pids = malloc(sizeof(int) * table->num_pids);
    if (!table->pids)
    {
        perror("Error allocating memory for PIDs");
        exit(1);
    }
    int i = 0;
    while(i < table->num_pids)
    {
        table->pids[i] = -1;
        i++;
    }

    table->envp = envp;
    table->ipids = 0;
}


int	open_fct_check(char *file, int i)
{
	int	filein;

	filein = 0;
	if (i == 0)
		filein = open(file, O_RDONLY);
	else if (i == 1)
		filein = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		filein = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (filein);
}

void    free_t_command(t_command *cmd)
{
    t_command *temp;

    while (cmd)
    {
        temp = cmd->next;
        freetab(cmd->args);
        free(cmd);
        cmd = temp;
    }
}

void    new_t_command(t_command *cmd)
{
    t_command   *new_cmd;
    new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
    {
        perror("Error allocating memory for new command");
        return ;
    }
    initialize_t_command(new_cmd);
    cmd->next = new_cmd;
}