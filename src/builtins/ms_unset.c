/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:40:39 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/26 18:15:12 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/// @brief Unsets a variable from the shell environment
/// @param args
/// @param cmd
/// @return
int	ms_unset(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		args_iterator;
	int		var_index;
	char	**env;
	int		var_after;

	(void)cmd;
	(void)args;
	env = mo_shell->shell_env;
	args_iterator = 1;
	while (args && args[args_iterator])
	{
		var_index = var_exst(args[args_iterator], env);
		var_after = 0;
		while (env[var_index + 1 + var_after] != NULL)
			var_after++;
		if (!var_after)
			(free(env[var_index]), env[var_index] = NULL);
		else
			ft_memmove(&env[var_index], &env[var_index + 1], sizeof(char *) \
				* (var_after + 1));
		args_iterator++;
	}
	return (0);
}
