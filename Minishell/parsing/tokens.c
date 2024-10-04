/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeannelefevre <jeannelefevre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/10/01 14:12:17 by jeannelefev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int count_tokens(char *input)
// {
//     int count = 0;
//     int i = 0;

//     while (input[i])
//     {
//         if (input[i] == ' ')
//         {
//             i++;
//             continue;
//         }
//         if (input[i] == '|' || input[i] == '>' || input[i] == '<')
//         {
//             count++;
//             if (input[i] == '>' && input[i + 1] == '>')
//                 i++;
//             i++;
//             continue;
//         }
//         count++;
//         while (input[i] && input[i] != ' ' && input[i] != '|'
//                 && input[i] != '>' && input[i] != '<')
//             i++;
//     }
//     return count;
// }



void process_tokens(char **tokens, t_command *cmd, int *j)
{
    int i = 0;

    // print_command(cmd);

    cmd->args = malloc(sizeof(char *) * 1024);
    if (!cmd->args)
    {
        perror("Error allocating memory for args");
        exit(1);
    }

    while (tokens[*j] && ft_strcmp(tokens[*j], "|"))
    {
        cmd->args[i] = ft_strdup(tokens[*j]);
        if (!cmd->args[i])
        {
            perror("Error duplicating token");
            exit(1);
        }
        i++;
        (*j)++;
    }
    cmd->args[i] = NULL;
}

t_command *tokenize_input(char *input, char **envp)
{
    char        **tokens;
    t_command   *cmd;
    t_command   *head;
    t_table     *table;
    int j = 0;

    if (!input)
        return NULL;
    cmd = malloc(sizeof(t_command));
    if (!cmd)
    {
        perror("Error allocating memory");
        return NULL;
    }
    table = malloc(sizeof(t_table));
    if (!table)
    {
        perror("Error allocating memory");
        return NULL;
    }
    initialize_t_command(cmd);
    initialize_t_main(table, envp);
    head = cmd;
    tokens = ft_split(input, ' ');
    while (tokens[j])
    {
        process_tokens(tokens, cmd, &j);
        if (tokens[j] && ft_strcmp(tokens[j], "|") == 0)
        {
            cmd->table->num_pids++;
            new_t_command(cmd);
            cmd = cmd->next;
            j++;
        }
    }
    printf("head\n");
    print_command(head);
    j = 0;
    freetab(tokens);
    print_command(head);
    return (head);
}