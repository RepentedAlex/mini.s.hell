/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_openings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:19:36 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/29 16:19:38 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	open_file_in(t_block *nav_block, t_cmd *nav_cmd, int mode)
{
	if (mode == 1)
	{
		if (nav_cmd->fd_i >= 0)
			(close(nav_cmd->fd_i), nav_cmd->fd_i = 0);
		nav_cmd->fd_i = open(nav_block->str, O_RDWR);
		if (nav_cmd->fd_i < 0)
			return (ERROR);
	}
	if (mode == 2)
	{
		if (nav_cmd->fd_i >= 0)
			(close(nav_cmd->fd_i), nav_cmd->fd_i = 0);
		nav_cmd->fd_i = open("heredoc", O_RDWR | O_CREAT, 0666);
		if (nav_cmd->fd_i < 0)
			return (ERROR);
		//TODO Fill heredoc
		// fill_heredoc();
	}
	return (NO_ERROR);
}

t_error	open_file_out(t_block *nav_block, t_cmd *nav_cmd, int mode)
{
	if (mode == 1)
	{
		if (nav_cmd->fd_o >= 0)
			(close(nav_cmd->fd_o), nav_cmd->fd_o = 0);
		nav_cmd->fd_o = open(nav_block->str, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (nav_cmd->fd_o < 0)
			return (ERROR);
	}
	if (mode == 2)
	{
		if (nav_cmd->fd_o >= 0)
			(close(nav_cmd->fd_o), nav_cmd->fd_o = 0);
		nav_cmd->fd_o = open(nav_block->str, O_RDWR | O_APPEND | O_CREAT, 0666);
		if (nav_cmd->fd_o < 0)
			return (ERROR);
	}
	return (NO_ERROR);
}

t_error	open_redir_i(t_cmd **cmd_head, t_block **block_head)
{
	t_block	*nav_block;
	t_cmd	*nav_cmd;

	nav_cmd = *cmd_head;
	nav_block = *block_head;
	while (nav_block)
	{
		if (nav_block->type == PIPE)
			nav_cmd = nav_cmd->next;
		else if (nav_block->type == REDIR_I)
		{
			nav_block = nav_block->next;
			if (open_file_in(nav_block, nav_cmd, 1) == ERROR)
				return (ERROR);
		}
		else if (nav_block->type == HEREDOC)
		{
			nav_block = nav_block->next;
			if (open_file_in(nav_block, nav_cmd, 2) == ERROR)
				return (ERROR);
		}
		nav_block = nav_block->next;
	}
	return (NO_ERROR);
}

t_error	open_redir_o(t_cmd **cmd_head, t_block **block_head)
{
	t_block	*nav_block;
	t_cmd	*nav_cmd;

	nav_cmd = *cmd_head;
	nav_block = *block_head;
	while (nav_block)
	{
		if (nav_block->type == PIPE)
			nav_cmd = nav_cmd->next;
		if (nav_block->type == REDIR_O)
		{
			nav_block = nav_block->next;
			if (open_file_out(nav_block, nav_cmd, 1) == ERROR)
				return (ERROR);
		}
		else if (nav_block->type == APPEND)
		{
			nav_block = nav_block->next;
			if (open_file_out(nav_block, nav_cmd, 2) == ERROR)
				return (ERROR);
		}
		nav_block = nav_block->next;
	}
	return (NO_ERROR);
}
