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
#include <libft.h>

/**
 * @brief 
 *
 * @return 
 */
int	numerator(char **filename)
{
	char	*num;
	int		fd;

	fd = -1;
	num = (char *)malloc(sizeof(char) * 4);
	if (!num)
		return (-1);
	num[0] = '0';
	while (num[0] <= '9')
	{
		num[1] = '0';
		while (num[1] <= '9')
{
			num[2] = '0';
			while (num[2] <= '9')
			{
				*filename = ft_strjoin("/tmp/heredoc", num);
				fd = open(*filename, O_RDONLY);
				if (fd == -1)
				{
					fd = open(*filename, O_RDWR | O_CREAT, 0666);
					return (free(num), fd);
				}
				free(*filename);
				(close(fd), fd = -1);
				num[2]++;
			}
			num[1]++;
		}
		num[0]++;
	}
	free(num);
	return (-1);
}

void	heredoc_filler(char *delimiter, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(delimiter, line) == 0)
		{
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	free(line);
}

void	heredoc_handler(t_block *nav_block, t_cmd *nav_cmd)
{
	char	*heredoc_name;

	(void)nav_block;
	heredoc_name = NULL;
	nav_cmd->fd_i = numerator(&heredoc_name);

	//Fill heredoc
	heredoc_filler(nav_block->str, nav_cmd->fd_i);
	close(nav_cmd->fd_i);
	open(heredoc_name, O_RDONLY);
	free(heredoc_name);
}

/**
 * @brief 
 *
 * @param nav_block 
 * @param nav_cmd 
 * @param mode 
 * @return 
 */
t_error	open_file_in(t_block *nav_block, t_cmd *nav_cmd, int mode)
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
		//TODO Fill heredoc
		heredoc_handler(nav_block, nav_cmd);
	}
	return (NO_ERROR);
}

t_error	open_file_out(t_block *nav_block, t_cmd *nav_cmd, int mode)
{
	if (mode == 1)
	{
		if (nav_cmd->fd_o != STDOUT_FILENO)
			(close(nav_cmd->fd_o), nav_cmd->fd_o = STDOUT_FILENO);
		nav_cmd->fd_o = open(nav_block->str, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (nav_cmd->fd_o < 0)
			return (ERROR);
	}
	if (mode == 2)
	{
		if (nav_cmd->fd_o != STDOUT_FILENO)
			(close(nav_cmd->fd_o), nav_cmd->fd_o = STDOUT_FILENO);
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
