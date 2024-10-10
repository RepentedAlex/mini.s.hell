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

/// @brief Performs the lexical analysis.
/// @param data Pointer to the structure holding the shell local variables.
/// @return ERROR on... error and NO_ERROR on... no error ! :)
t_error	lexing(t_shell_env *data)
{
	tokeniser(data);
	if (data->tokens == NULL)
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
	t_shell_env	shell_env;

	(void)argc, (void)argv, (void)envp;
	ft_bzero(&shell_env, sizeof(t_shell_env));
	shell_env.tokens = malloc(sizeof(t_token *));
	while (1)
	{
		shell_env.buffer = readline(PROMPT);
		if (check_quotes(shell_env.buffer) == ERROR)
			printf("Error : Quotes are not closed.\n");
		if (lexing(&shell_env))
			printf("Eror : Couldn't perform lexical analysis.\n");
		free(shell_env.buffer);
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
