/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:53:08 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/19 11:53:11 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/// @brief Prints the current working dir as per the PWD variable in the shell
/// environment.
/// @param args
/// @param cmd
/// @return
int	ms_pwd(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		var_index;
	char	*var_content;

	(void)cmd;
	(void)args;
	var_index = var_exst("PWD", mo_shell->shell_env);
	var_content = mo_shell->shell_env[var_index];
	while (*var_content != '=')
		var_content++;
	var_content++;
	write(1, var_content, ft_strlen(var_content));
	write(1, "\n", 1);
	return (0);
}
