/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_openings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:19:36 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/04 18:09:15 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/**
 * @brief 
 *
 * @param nav_block 
 * @param nav_cmd 
 * @param mode 
 * @return 
 */
t_error	open_file_in(t_block *nav_block, t_cmd *nav_cmd, int mode, t_mo_shell \
	*mo_shell)
{
	if (mode == 1)
	{
		if (nav_cmd->fd_i != STDIN_FILENO)
			(close(nav_cmd->fd_i), nav_cmd->fd_i = STDIN_FILENO);
		nav_cmd->fd_i = open(nav_block->str, O_RDWR);
		if (nav_cmd->fd_i < 0)
			return (ERROR);
	}
	if (mode == 2)
	{
		if (nav_cmd->fd_i != STDIN_FILENO)
			(close(nav_cmd->fd_i), nav_cmd->fd_i = STDIN_FILENO);
		heredoc_handler(nav_block, nav_cmd, mo_shell);
	}
	return (NO_ERROR);
}

/// @brief 
/// @param nav_block
/// @param nav_cmd 
/// @param mode 1 == truncate ; 2 == append
/// @return 
t_error	open_file_out(t_block *nav_block, t_cmd *nav_cmd, int mode)
{
	if (mode == 1)
	{
		if (nav_cmd->fd_o != STDOUT_FILENO)
			(close(nav_cmd->fd_o), nav_cmd->fd_o = STDOUT_FILENO);
		nav_cmd->fd_o = open(nav_block->str, O_RDWR | O_CREAT | O_TRUNC, \
			0666);
		if (nav_cmd->fd_o < 0)
			return (ERROR);
		write(nav_cmd->fd_o, "", 0);
	}
	if (mode == 2)
	{
		if (nav_cmd->fd_o != STDOUT_FILENO)
			(close(nav_cmd->fd_o), nav_cmd->fd_o = STDOUT_FILENO);
		nav_cmd->fd_o = open(nav_block->str, O_RDWR | O_APPEND | O_CREAT, \
			0666);
		if (nav_cmd->fd_o < 0)
			return (ERROR);
	}
	return (NO_ERROR);
}
