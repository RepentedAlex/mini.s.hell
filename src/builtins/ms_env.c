/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:44:23 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/19 13:44:25 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/// @brief Lists all the variable of the current environment
/// @param args
/// @param cmd
/// @return
int	ms_env(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		i;
	char	**env;

	(void)cmd;
	(void)args;
	env = mo_shell->shell_env;
	i = 0;
	while (mo_shell->shell_env[i] != NULL)
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
