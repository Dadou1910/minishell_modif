/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeannelefevre <jeannelefevre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:01:59 by jealefev          #+#    #+#             */
/*   Updated: 2024/10/01 14:46:07 by jeannelefev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

#define READ_END 0
#define WRITE_END 1
typedef struct s_table
{
    char **envp;
    int num_pids;
    int *pids;
    int ipids;
}   t_table;

typedef struct s_command
{
    char    **args;         // Command  + command arguments (e.g., ["-l", "/home"])
    int     fd_in;          // File descriptor of the input file in the block
    int     fd_out;         // File descriptor of the output file in the block
    int *p;                 // 0 or 1 for read_end and write_end
    int pprev;              // to redirect stdin to read_end of pipe
    int pipe_count;         // number of pipes
    struct s_command *next; // Pointer to the next command (for pipelines)
    t_table *table;
} t_command;

typedef struct
{
    int i;
    int sq_open;
    int dq_open;
} t_state;

// =========================================================================
//                                PARSING
// =========================================================================

void    initialize_t_command(t_command *cmd);
int     open_fct_check(char *file, int i);
void    free_t_command(t_command *cmd);
void    new_t_command(t_command *cmd);
void    add_line_to_history(const char *line);
t_command   *tokenize_input(char *input);
t_command   *fill_t_command(char *input);

// Expand


t_command   *parse_pipeline_commands(char **tokens);

void print_command(t_command *cmd);

// =========================================================================
//                                EXECUTION
// =========================================================================

int launch(t_command *cmd);
void execute(t_command *cmd);
int deal_in_pipe(t_command *cmd);
int deal_out_pipe(t_command *cmd);
void freetab(char **tab);


// =========================================================================
//                                BUILTINS
// =========================================================================

// int is_builtins(t_command *cmd);
int is_builtins(t_command *cmd);
int echo(char **args);
int	cd(char **tab);
int pwd(void);
int env(char **envp);
int unset(char **envp, const char *var);
#endif
