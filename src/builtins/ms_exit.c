/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:12:03 by llabonde          #+#    #+#             */
/*   Updated: 2024/11/05 16:16:20 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
//autre

static bool	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	ft_skip_spaces_and_get_sign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

static int	exit_gen(char *s, t_mo_shell *mo_shell)
{
	int					i;
	int					sign;
	int					exit_s;
	unsigned long long	result;

	i = 0;
	sign = 1;
	ft_skip_spaces_and_get_sign(s, &i, &sign);
	if (!ft_isnumber(s + i))
	{
		exit_s = ft_err_msg((t_err){2, ERRMSG_NUMERIC_REQUI, s});
		(garbage_collect(mo_shell, 1), exit(exit_s));
	}
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		if (result > __LONG_MAX__)
		{
			exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
			(garbage_collect(mo_shell, 1), exit(exit_s));
		}
		i++;
	}
	return ((unsigned long long)(result * sign) % 256);
}

/// @brief Exit builtin
/// @param args Arguments for the command
/// @param mo_shell Pointer to the Mother Shell structure
/// @return 
int	ms_exit(char **args, t_mo_shell *mo_shell)
{
	int	exit_s;
	
	exit_s = mo_shell->last_exit_status;
	if (args && args[0])
	{
		if (args[1] && ft_isnumber(args[0]))
		{
			exit_s = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_TOO_MANY_ARGS, NULL});
			(garbage_collect(mo_shell, 1), exit(exit_s));
		}
		else
			exit_s = exit_gen(args[0], mo_shell);
	}	
	(garbage_collect(mo_shell, 1), exit(exit_s));
	return (0);
}