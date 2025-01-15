/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:49:16 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/03 14:26:14 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

pid_t	g_signal_pid;

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
		g_signal_pid = 0;
		mo_shell->og_input = readline(PROMPT);
		if (!check_input(mo_shell))
			break ;
		g_signal_pid = 1;
		if (parsing(mo_shell) == ERROR || execution(mo_shell) == ERROR)
			continue ;
	}
	garbage_collect(mo_shell, 1);
	return (ft_putstr_fd("exit\n", STDOUT_FILENO), EXIT_SUCCESS);
}

int	main(const int argc, char *argv[], char *envp[])
{
	t_mo_shell	mo_shell;

	mo_shell.shell_env = NULL;
	if (envp[0] == NULL)
		init_min_env(&mo_shell);
	else
	{
		mo_shell.shell_env = copy_env(envp);
		if (!mo_shell.shell_env)
			return (ERROR);
	}
	g_signal_pid = 0;
	signals();
	mo_shell.last_exit_status = 0;
	mo_shell.og_input = NULL;
	mo_shell.clean_input = NULL;
	mo_shell.expanded_input = NULL;
	mo_shell.splitted_input = NULL;
	mo_shell.cmds_table = NULL;
	if (init_shell() == ERROR)
		return (ERROR);
	return (mini_s_hell(argc, argv, envp, &mo_shell));
}
