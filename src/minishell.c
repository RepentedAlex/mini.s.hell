/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:49:16 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/08 11:49:47 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	check_redir_syntax(char *str)
{

}

bool	look_for_redir(char *str)
{
	(void)str;
}

t_error	check_pipes_syntax(char *str)
{
	(void)str;
}

bool	look_for_pipes(char *str)
{
	(void)str;
}

void	expand_variables(char *src)
{
	(void)src;
}

/// @brief Performs the lexical analysis.
/// @param data Pointer to the structure holding the shell local variables.
/// @return ERROR on... error and NO_ERROR on... no error ! :)
t_error	lexing(t_mo_shell *data)
{
	tokeniser(data);
	if (!data->tokens)
		return (ERROR);
	identify_tokens(data->tokens);
	return (NO_ERROR);
}

/// @brief The main mini.s.hell function ! :D
/// @param argc The number of arguments passed via the CLI.
/// @param argv The arguments passed via the CLI.
/// @param envp The environment variables.
/// @return EXIT_FAILURE on error and EXIT_SUCCESS otherwise.
int	mini_s_hell(int argc, char *argv[], char *envp[])
{
	t_mo_shell	shell_env;

	(void)argc, (void)argv, (void)envp;
	ft_bzero(&shell_env, sizeof(t_mo_shell));
	shell_env.tokens = malloc(sizeof(t_token *));
	while (1)
	{
		//0. Read input
		shell_env.og_input = readline(PROMPT);

		//1. Check for open quotes
		if (check_open_quotes(shell_env.og_input) == ERROR)
			return (printf("mini.s.hell: quotes are not closed\n"), ERROR);

		//2. Expand variables
		expand_variables(shell_env.og_input);						// TODO

		//2,5 ft_strdup og_input into a new t_list node to set up future splits


		//3. Check for pipes
		if (look_for_pipes(shell_env.og_input) == true)			// TODO
		{
			//3.1 If pipes, check they are syntactically valid
			if (check_pipes_syntax(shell_env.og_input) == ERROR)	// TODO
				return (printf("mini.s.hell: syntax error near unexpected token '|'\n"), ERROR);

			//3.1.1 Create blocks, separated by pipes
			// ft_split(shell_env.buffer, '|');					// TODO + define in which field to assign
		}

		// 4. Check redirections < , <<, >>, >
		if (look_for_redir(shell_env.og_input) == true)			// TODO
		{
			// 4.1 If redirections, check they are syntactically valid
			if (check_redir_syntax(shell_env.og_input) == ERROR)	// TODO
				return (printf("mini.s.hell: \n"), ERROR);
		}

		//
		if (lexing(&shell_env) == ERROR)
			break ;
		free(shell_env.og_input);
	}
	garbage_collect(&shell_env);
	return (EXIT_SUCCESS);
}

//TODO Might be a good idea to implement a non-interactive version.
int	main(const int argc, char *argv[], char *envp[])
{
	if (isatty(STDIN_FILENO) == 1)
		return (mini_s_hell(argc, argv, envp));
	return (0);
}
