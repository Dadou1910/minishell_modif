/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeannelefevre <jeannelefevre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:03:20 by jealefev          #+#    #+#             */
/*   Updated: 2024/10/01 14:58:45 by jeannelefev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>

void add_line_to_history(const char *line)
{
    if (line && *line) {
        add_history(line);  // Add the line to the in-memory history
    }
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

char *get_prompt()
{
    char cwd[1024];
    char *tmp = NULL;
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        tmp = ft_strjoin(cwd, " >> ");
    return(tmp);
}

void print_command(t_command *cmd)
 {
    int i = 0;
    printf("Arguments: ");
    if (cmd->args) 
    {
        while (cmd->args[i]) 
        {
            printf("%s ", cmd->args[i]);
            i++;
        }
    }
    printf("\n");
    printf("fd_in: %d\n", cmd->fd_in);
    printf("fd_out: %d\n", cmd->fd_out);
    if (cmd->p)
        printf("Pipe read_end: %d, write_end: %d\n", cmd->p[0], cmd->p[1]);
    else
        printf("No pipe defined.\n");
    printf("Previous pipe input (pprev): %d\n", cmd->pprev);
    printf("Pipe count: %d\n", cmd->pipe_count);
    if (cmd->next)
        printf("Next command exists.\n");
    else
        printf("No next command.\n");
    if (cmd->table)
        printf("Table defined.\n");
    else
        printf("Table is NULL.\n");
}
/*
int main(int argc, char **argv, char **envp)
{
    char *line;
    t_command *cmd;
    line = NULL;
    (void)argc;
    (void)argv;
    (void)envp;
    while (1)
    {      
        line = readline(get_prompt());
        printf("READLINE RESULT -----> %s\n", line);
        if (!line)
        {
            perror("readline");
            break;
        }
        add_line_to_history(line);

        if (ft_strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }
        // (void)cmd;
        // if (line[0] != '\0')
        // {
        cmd = fill_t_command(line, envp);
        printf("\nBefore printing command, args[0]: %s\n\n", cmd->args[0]);
        print_command(cmd);
        if (!cmd)
        {
            free(line);
            perror("Failed to parse command");
            continue;
        }
            // launch(cmd);
        // }
        free(line);
    }
    return 0;
}
*/