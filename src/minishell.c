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

/// @brief Breaks a string in an array of tokens.
/// @param str The input string.
/// @return A 2D array holding all the tokens + NULL pointer at the end.
char	**tokeniser(char *str)
{
	char	**ret;
	int		leading_ws;
	int		nb_token;
	bool	in_word;

	leading_ws = count_leading_whitespace(str);
	if (leading_ws)
		trim_leading_whitespace(str, leading_ws);
	nb_token = count_tokens(str);
	ret = (char **)malloc(sizeof(char *) * (nb_token + 1));
	if (!ret)
		return (NULL);
	in_word = false;
	ret[nb_token] = NULL;
	nb_token --;
	split_str(str, ret, &nb_token, &in_word);
	return (ret);
}

/// @brief Performs the lexical analysis.
/// @param data Pointer to the structure holding the shell local variables.
/// @return ERROR on... error and NO_ERROR on... no error ! :)
t_error	lexing(t_shell_env *data)
{
	data->tokens = tokeniser(data->buffer);
	return (NO_ERROR);
}

/// @brief The main mini.s.hell function ! :D
/// @param argc The number of arguments passed via the CLI.
/// @param argv The arguments passed via the CLI.
/// @param envp The environment variables.
/// @return EXIT_FAILURE on error and EXIT_SUCCESS otherwise.
int	mini_s_hell(int argc, char *argv[], char *envp[])
{
	t_shell_env	data;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		data.buffer = readline(PROMPT);
		if (data.buffer[0] == '\0')
			break ;
		data.tokens = tokeniser(data.buffer);
		if (data.tokens == NULL)
			return (EXIT_FAILURE);
		garbage_collect(&data);
	}
	garbage_collect(&data);
	return (EXIT_SUCCESS);
}

int	main(const int argc, char *argv[], char *envp[])
{
	if (isatty(STDIN_FILENO) == 1)
		return (mini_s_hell(argc, argv, envp));
	return (0);
}
