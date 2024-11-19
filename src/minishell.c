/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:49:16 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/05 15:54:05 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	words_in_str(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ':' || str[i] != '!')
			return (true);
		i++;
	}
	return (false);
}

/// @brief The main mini.s.hell function ! :D
/// @param argc The number of arguments passed via the CLI.
/// @param argv The arguments passed via the CLI.
/// @param envp The environment variables.
/// @param mo_shell
/// @return EXIT_FAILURE on error and EXIT_SUCCESS otherwise.
int	mini_s_hell(int argc, char *argv[], char *envp[], t_mo_shell *mo_shell)
{
	(void)argc, (void)argv, (void)envp;
	splash_screen();
	while (1)
	{
		garbage_collect(mo_shell, 0);
		mo_shell->og_input = readline(PROMPT);
		if (mo_shell->og_input[0] == '\0' || words_in_str(mo_shell->og_input) == false)
			continue ;
		if (mo_shell->og_input && *mo_shell->og_input)
			add_history(mo_shell->og_input);
		if (parsing(mo_shell) == ERROR)
			continue ;
		execution(mo_shell);
	}
	garbage_collect(mo_shell, 1);
	return (EXIT_SUCCESS);
}

t_error	init_shell()
{
	int	shell_terminal;
	int	shell_is_interactive;

	shell_terminal = STDIN_FILENO;
	shell_is_interactive = 0;
	shell_is_interactive = isatty(shell_terminal);
	if (shell_is_interactive == 1)
		return (NO_ERROR);
	return (ERROR);
}

int	main(const int argc, char *argv[], char *envp[])
{
	t_mo_shell	mo_shell;

	ft_bzero(&mo_shell, sizeof(t_mo_shell));
	mo_shell.shell_env = copy_env(envp);
	if (init_shell() == ERROR)
		return (ERROR);
	return (mini_s_hell(argc, argv, envp, &mo_shell));
}
