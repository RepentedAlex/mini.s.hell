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
		if (mo_shell->og_input[0] == '\0')
			break ;
		if (mo_shell->og_input && *mo_shell->og_input)
			add_history(mo_shell->og_input);
		if (parsing(mo_shell) == ERROR)
			continue ;
		// == == == TRANSITION VERS l'EXEC == == ==
		launch_builtins(mo_shell->splitted_input);
	}
	garbage_collect(mo_shell, 1);
	return (EXIT_SUCCESS);
}

//TODO Might be a good idea to implement a non-interactive version.
int	main(const int argc, char *argv[], char *envp[])
{
	t_mo_shell	mo_shell;

	ft_bzero(&mo_shell, sizeof(t_mo_shell));
	mo_shell.shell_env = copy_env(envp);
	if (isatty(STDIN_FILENO) == 1)
		return (mini_s_hell(argc, argv, envp, &mo_shell));
	return (0);
}
