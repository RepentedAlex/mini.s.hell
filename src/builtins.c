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

int	ms_builtin(char **args)
{
	t_builtin	builtins_array[] = {
		{"cd", ms_cd},
		{"echo", ms_echo},
		{"env", ms_env},
		{"exit", ms_exit},
		{"export", ms_export},
		{"pwd", ms_pwd},
		{"unset", ms_unset}
	};
}
