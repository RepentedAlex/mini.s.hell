/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:22:23 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/05 15:47:55 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtins.h"

/// @brief
/// @param args
/// @return
int	ms_pwd(char **args, t_mo_shell *mo_shell)
{
	int	i;

	(void)mo_shell;
	(void)args;
	i = 0;
	return (i);
}

/// @brief
/// @param args
/// @return
int	ms_unset(char **args, t_mo_shell *mo_shell)
{
	int	i;

	(void)mo_shell;
	(void)args;
	i = 0;
	return (i);
}
