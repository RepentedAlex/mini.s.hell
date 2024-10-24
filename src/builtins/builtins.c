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
#include "minishell_builtins.h"
#include "libft.h"

// apetitco
// Bon le tableau peut pas être déclaré et initialisé en même temps donc faudra
//faire autrement
t_builtin	*get_builtin_array(void)
{
	static t_builtin	builtins_array[] = {\
		{"cd", ms_cd}, \
		{"echo", ms_echo}, \
		{"env", ms_env}, \
		{"exit", ms_exit}, \
		{"export", ms_export}, \
		{"pwd", ms_pwd}, \
		{"unset", ms_unset}, \
		{NULL, NULL}
	};

	return (builtins_array);
}

bool	is_builtin(char *str)
{
	t_builtin	*builtins_array;
	int			i;

	if (!str)
		return (false);
	builtins_array = get_builtin_array();
	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str, builtins_array[i].name) == 0)
			return (true);
		i++;
	}
	return (false);
}

/// @brief Check if the command block is a builtin or not
/// @param command The block.
/// @return true if it's a builtin, false if not in the builtins_array.
int	(*launch_builtins(t_cmd *command))(char **str)
{
	t_builtin	*builtins_array;
	int			i;

	if (!command)
		return (NULL);
	builtins_array = get_builtin_array();
	i = -1;
	while (builtins_array[++i].name != NULL)
		if (ft_strcmp(command->cmd, builtins_array[i].name) == 0)
			return (builtins_array[i].builtin_func);
	return (NULL);
}
