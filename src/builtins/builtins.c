/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:30:37 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/09 19:30:37 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief
/// @param args
/// @return
int	ms_cd(char **args)
{
	int	i;

	(void)args;
	i = 0;
	return (i);
}

/// @brief
/// @param args
/// @return
int	ms_echo(char **args)
{
	int	i;

	(void)args;
	i = 0;
	return (i);
}

/// @brief
/// @param args
/// @return
int	ms_env(char **args)
{
	int	i;

	(void)args;
	i = 0;
	return (i);
}

/// @brief
/// @param args
/// @return
int	ms_exit(char **args)
{
	int	i;

	(void)args;
	i = 0;
	return (i);
}

/// @brief
/// @param args
/// @return
int	ms_export(char **args)
{
	int	i;

	(void)args;
	i = 0;
	return (i);
}

/// @brief
/// @param args
/// @return
int	ms_pwd(char **args)
{
	int	i;

	(void)args;
	i = 0;
	return (i);
}

/// @brief
/// @param args
/// @return
int	ms_unset(char **args)
{
	int	i;

	(void)args;
	i = 0;
	return (i);
}

// apetitco
// Bon le tableau peut pas être déclaré et initialisé en même temps donc faudra
//faire autrement
t_builtin *get_builtin_array(void)
{
	static t_builtin	builtins_array[] = {
		{"cd", ms_cd},
		{"echo", ms_echo},
		{"env", ms_env},
		{"exit", ms_exit},
		{"export", ms_export},
		{"pwd", ms_pwd},
		{"unset", ms_unset},
		{NULL, NULL}
	};
	return (builtins_array);
}

/// @brief Check if the command block is a builtin or not
/// @param block The block.
/// @return true if it's a builtin, false if not in the builtins_array.
int (*launch_builtins(t_block *block))(char **)
{
	t_builtin	*builtins_array;
	int			i;

	if (!block)
		return (NULL);
	builtins_array = get_builtin_array();
	i = -1;
	while (builtins_array[++i].name != NULL)
		if (ft_strcmp(block->str, builtins_array[i].name) == 0)
			return (builtins_array[i].builtin_func);
	return (NULL);
}
