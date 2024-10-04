/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/04 10:50:08 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *expand_env_var_1(const char *input, t_state *state)
{
    char *env = NULL;

    if (!ft_strncmp(&input[state->i + 1], "PATH", 4))
    {
        env = getenv("PATH");
        state->i += 4;
    }
    else if (!ft_strncmp(&input[state->i + 1], "HOME", 4))
    {
        env = getenv("HOME");
        state->i += 4;
    }
    else if (!ft_strncmp(&input[state->i + 1], "PWD", 3))
    {
        env = getenv("PWD");
        state->i += 3;
    }
    else if (!ft_strncmp(&input[state->i + 1], "OLDPWD", 6))
    {
        env = getenv("OLDPWD");
        state->i += 6;
    }
    return (env);
}

char *expand_env_var_2(const char *input, t_state *state)
{
    char *env = NULL;

    if (!ft_strncmp(&input[state->i + 1], "SHLVL", 5))
    {
        env = getenv("SHLVL");
        state->i += 5;
    }
    else if (!ft_strncmp(&input[state->i + 1], "_", 1))
    {
        env = getenv("_");
        state->i += 1;
    }
    else if (!ft_strncmp(&input[state->i + 1], "USER", 4))
    {
        env = getenv("USER");
        state->i += 4;
    }
    else if (!ft_strncmp(&input[state->i + 1], "TERM", 4))
    {
        env = getenv("TERM");
        state->i += 4;
    }
    return (env);
}

char *process_char(const char *input, char *result, t_state *state)
{
    char *env;
    size_t result_size = 4096;

    env = NULL;
    while (input[state->i] != '\0')
    {
        // Handle single quote: only add if inside double quotes or in a balanced string
        if (input[state->i] == '\'' && !state->dq_open)
        {
            state->sq_open = !state->sq_open;  // Toggle single quote state
            if (state->sq_open || !state->sq_open) // Only add when part of a string
                ft_strlcat(result, "'", result_size); // Add the single quote to result
        }
        // Handle double quote: only add if inside single quotes or in a balanced string
        else if (input[state->i] == '"' && !state->sq_open)
        {
            state->dq_open = !state->dq_open;  // Toggle double quote state
            if (state->dq_open || !state->dq_open)  // Only add when part of a string
                ft_strlcat(result, "\"", result_size); // Add the double quote to result
        }
        // Handle environment variable expansion when not inside single quotes
        else if (input[state->i] == '$' && !state->sq_open)
        {
            // Try to expand the environment variable
            env = expand_env_var_1(input, state);
            if (!env)
                env = expand_env_var_2(input, state);

            if (env)
                ft_strlcat(result, env, result_size);  // Append the expanded variable
        }
        // Handle normal characters
        else
        {
            char temp[2] = {input[state->i], '\0'};
            ft_strlcat(result, temp, result_size);  // Append normal characters to the result
        }
        state->i++;
        process_char(input, result, state);
    }
    return (result);
}

// void process_char(const char *input, char *result, t_state *state)
// {
//     char *env;
//     size_t result_size;
    
//     result_size = sizeof(result);
//     env = NULL;
//     if (input[state->i] == 0)
//         return;

//     if (input[state->i] == '\'' && !state->dq_open)
//         state->sq_open = !state->sq_open;

//     else if (input[state->i] == '"' && !state->sq_open)
//         state->dq_open = !state->dq_open;

//     else if (input[state->i] == '$' && !state->sq_open)
//     {
//         env = expand_env_var_1(input, state);
//         if (!env)
//             env = expand_env_var_2(input, state);
//         if (env)
//             ft_strlcat(result, env, result_size);
//     }
//     else
//     {
//         char temp[2] = {input[state->i], '\0'};
//         ft_strlcat(result, temp, 1);
//     }
//     state->i++;
//     process_char(input, result, state);
// }

// int retrieve_exit_status(char *env_var, t_command *cmd, int exit_status)
// {
//     if (ft_strcmp(env_var, "?") == 0)
//         return (exit_status);
// }

void allocate_resources(char **result, t_state **state)
{
    *result = malloc(sizeof(char) * 4096);  // Allocate enough space for the result string
    if (!(*result))
    {
        perror("Error allocating memory for result");
        exit(1);
    }
    (*result)[0] = '\0';  // Initialize the result string to an empty string

    *state = malloc(sizeof(t_state));  // Allocate memory for the state structure
    if (!(*state))
    {
        perror("Error allocating memory for state");
        free(*result);  // Free allocated memory for result if state allocation fails
        exit(1);
    }
    (*state)->i = 0;
    (*state)->sq_open = 0;
    (*state)->dq_open = 0;
}

int main(int argc, char **argv, char **envp)
{
    t_command   *cmd;
    char        *line;
    char        *result;
    t_state     *state;
    (void)argc;
    (void)argv;

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
        cmd = fill_t_command(line, envp);
        // print_command(cmd);
        if (cmd->args[1][0] == '\'' || cmd->args[1][0] == '\"' || cmd->args[1][0] == '$')
        {
            allocate_resources(&result, &state);
            printf("\nRESULT -----> %s\n", process_char(cmd->args[1], result, state));
        }
        free(line);
    }
}
