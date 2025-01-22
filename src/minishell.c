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

int	err_msg(char *err_msg, char *element)
{
	int		stdout_copy;
	int		printf_ret;

	stdout_copy = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf_ret = printf(err_msg, element);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	return (printf_ret);
}

char	*new_prompt(char *prompt)
{
	int		stdout_copy;
	char	*line;

	stdout_copy = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	line = readline(prompt);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	return (line);
}

/// @brief The main mini.s.hell function ! :D
/// @param argc The number of arguments passed via the CLI.
/// @param argv The arguments passed via the CLI.
/// @param envp The environment variables.
/// @param mo_shell
/// @return EXIT_FAILURE on error and EXIT_SUCCESS otherwise.
int	mini_s_hell(t_mo_shell *mo_shell)
{
	splash_screen();
	while (1)
	{
		garbage_collect(mo_shell, COLLECT_CMD);
		g_signal_pid = 0;
		mo_shell->og_input = new_prompt(PROMPT);
		if (string_is_only_ifs(mo_shell->og_input))
			continue ;
		if (!check_input(mo_shell))
			break ;
		g_signal_pid = 1;
		if (parsing(mo_shell) == ERROR || execution(mo_shell) == ERROR)
			continue ;
	}
	garbage_collect(mo_shell, COLLECT_ALL);
	return (printf("exit\n"), EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mo_shell	mo_shell;

	(void)argv;
	(void)argc;
	ft_bzero(&mo_shell, sizeof(t_mo_shell));
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
	if (init_shell() == ERROR)
		return (ERROR);
	return (mini_s_hell(&mo_shell));
}
