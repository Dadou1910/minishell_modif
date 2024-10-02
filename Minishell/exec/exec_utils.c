/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeannelefevre <jeannelefevre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/10/01 13:07:29 by jeannelefev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdlib.h>

void freetab(char **tab) 
{
    if (tab) {
        int i = 0;
        while (tab[i]) {
            free(tab[i]);  // Libérer chaque chaîne
            i++;
        }
        free(tab);  // Libérer le tableau lui-même
    }
}

char *find_path(char *cmd)
{
    char *path = getenv("PATH");
    if (!path)
		return NULL;
    char **pathoche = ft_split(path, ':');
    char *res;
    for (int i = 0; pathoche[i]; i++) {
        char *tmp = ft_strjoin(pathoche[i], "/");
        if (!tmp)
			return(freetab(pathoche), NULL);
        res = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!res)
		return(freetab(pathoche), NULL);
        if (access(res, X_OK) == 0) {
            freetab(pathoche);
            return res;
        }
        free(res);
    }
    freetab(pathoche);
    return NULL;
}



void execute(t_command *cmd)
{
    char *pathoche;

    if (!cmd || !cmd->args || !cmd->args[0])
        perror("invalid command");

    if (ft_strncmp(cmd->args[0], "/", 1) == 0)
        pathoche = cmd->args[0];
    else
        pathoche = find_path(cmd->args[0]);
    if (!pathoche)
        perror("command not found");
    if (execve(pathoche, cmd->args, cmd->table->envp) == -1)
    {
        free(pathoche);
        perror("command execution failed");
    }
}

