/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:20:53 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/04 17:37:43 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	check_cmd_bonus(int argc, char **argv, char **envp, int i)
{
	char	*str;
	char	**command;

	while (argv[i] && i < argc - 1)
	{
		if ((i < argc - 1) && ft_strcmp(argv[i], "/bin/") == 0)
			bin_check(argv[i]);
		else
		{
			command = ft_split(argv[i], ' ');
			if (command == NULL)
				ft_error("malloc");
			str = path(command[0], envp);
			if (str == NULL || argv[i][0] == '.' || argv[i][0] == '\0')
			{
				(free(str), freetab(command));
				command_not_found(argv[i]);
			}
			(free(str), freetab(command));
		}
		i++;
	}
}

void close_fd(int in_fd, int out_fd)
{
	if(in_fd)
		close(in_fd);
	if(out_fd)
		close(out_fd);
}

void ft_error_c(int in_fd, int out_fd, char *str)
{
	perror(str);
	close_fd(in_fd, out_fd);
	exit(EXIT_FAILURE);
}

void open_files(char **argv, int *in_fd, int *out_fd)
{
	*in_fd = open_fct(argv[1], ft_atoi(argv[0]));
	*out_fd = open_fct(argv[3], ft_atoi(argv[0]));
	if (out_fd < 0 || in_fd < 0)
	ft_error_c(*in_fd, *out_fd, "Erreur lors de l'ouverture d'un fichier");
}
void deal_one_cmd(char **argv, char **envp)
{
    pid_t pid;
    int in_fd = 0;
    int out_fd = 0;

    open_files(argv, &in_fd, &out_fd);
    pid = fork();
    if (pid < 0) {
        ft_error_c(in_fd, out_fd, "Erreur lors du fork");
    }

    if (pid == 0) {
        if (dup2(in_fd, STDIN_FILENO) < 0)
            ft_error_c(in_fd, out_fd, "Erreur lors de la redirection de l'entrée standard");

        if (dup2(out_fd, STDOUT_FILENO) < 0)
            ft_error_c(in_fd, out_fd, "Erreur lors de la redirection de la sortie standard");

        close_fd(in_fd, out_fd);
        char **commande = ft_split(argv[2], ' ');
        execve(path(commande[0], envp), commande, envp);

        perror("Erreur lors de l'exécution de la commande");
        exit(EXIT_FAILURE);
    } else {
        close_fd(in_fd, out_fd);
        wait(NULL);
	}
}

void	check_argv_bonus(int argc, char **argv, char **envp)
{
	int	i;

	i = 2;
	if (argc < 5 || argc > 1026)
	{
		deal_one_cmd(argv, envp);
	}
	while (argv[i])
	{
		if (!argv[i])
		{
			write(1, "Argv error\n", 11);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (!envp[0])
	{
		if (check_envp(argc, argv) == 0)
			return ;
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
		i++;
	check_cmd_bonus(argc, argv, envp, i);
}

char	*ft_ligne(char *str)
{
	char	*res;
	int		i;
	int		j;
	size_t	len;

	i = 3;
	j = 0;
	len = strlen(str);
	if (len < 4)
	{
		return (NULL);
	}
	res = (char *)malloc(sizeof(char) * (len - 2));
	if (res == NULL)
	{
		return (NULL);
	}
	while (str[i] && str[i] != '\n')
	{
		res[j] = str[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}
