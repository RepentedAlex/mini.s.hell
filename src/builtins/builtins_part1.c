/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:21:11 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/05 16:17:54 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtins.h"

/// @brief
/// @param args
/// @param cmd
/// @return
int	ms_cd(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int	i;

	(void)mo_shell;
	(void)cmd;
	(void)args;
	i = 0;
	return (i);
}

// /// @brief
// /// @param args
// /// @return
// int	ms_echo(char **args, t_mo_shell *mo_shell)
// {
// 	int	i;
// 	(void)mo_shell;
//
// 	(void)args;
// 	i = 0;
// 	return (i);
// }

/// @brief
/// @param args
/// @param cmd
/// @return
int	ms_env(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int	i;

	(void)mo_shell;
	(void)cmd;
	(void)args;
	i = 0;
	return (i);
}

// /// @brief
// /// @param args
// /// @return
// int	ms_exit(char **args, t_mo_shell *mo_shell)
// {
// 	(void)mo_shell;
// 	int	i;

// 	(void)args;
// 	i = 0;
// 	return (i);
// }

/// @brief
/// @param args
/// @param cmd
/// @return
int	ms_export(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int	i;

	(void)mo_shell;
	(void)cmd;
	(void)args;
	i = 0;
	return (i);
}
