/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:47 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 13:38:50 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

t_error	init_min_env(t_mo_shell *mo_shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ERROR);
	(void)mo_shell;
	mo_shell->shell_env = NULL;
	mo_shell->shell_env = (char **)malloc(sizeof(char *));
	mo_shell->shell_env[0] = ft_strdup("PWD=");
	mo_shell->shell_env[0] = append(mo_shell->shell_env[0], cwd, \
		ft_strlen(cwd));
	add_str_to_ra(&mo_shell->shell_env, "SHLVL=1");
	add_str_to_ra(&mo_shell->shell_env, "_=/usr/bin/env");
	return (NO_ERROR);
}

t_error	init_shell(void)
{
	// int	shell_terminal;
	// int	shell_is_interactive;
	//
	// shell_terminal = STDIN_FILENO;
	// shell_is_interactive = 0;
	// shell_is_interactive = isatty(shell_terminal);
	// if (shell_is_interactive == 1)
		return (NO_ERROR);
	return (ERROR);
}
