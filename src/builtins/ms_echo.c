/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:19:56 by llabonde          #+#    #+#             */
/*   Updated: 2024/11/05 16:27:18 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

bool	echo_check_option(char *str)
{
	int	i;

	i = 1;
	while (str && str[i] && str[i] == 'n')
	{
		i++;
	}
	if (!str[i])
		return (true);
	return (false);
}

/// @brief
/// @param
/// @param mo_shell
/// @param cmd
/// @return
int	ms_echo(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		i;
	bool	option;

	(void)mo_shell;
	(void)cmd;
	i = 0;
	option = false;
	while (args && args[i] && args[i][0] == '-')
	{
		if (echo_check_option(args[i]) == true)
			option = true;
		else
			break ;
		i++;
	}
	while (args && args[i])
	{
		if (i == 0)
		{
			if (args[i][0] == '-' && args[i][1] == 'n' && args[i][2] == '\0')
			{
				// Gestion des erreurs a preciser
				option = true;
				i++;
			}
		}
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	return (0);
}
