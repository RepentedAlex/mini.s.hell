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
	ft_memset(num, '\0', 4);
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


//TODO Rajouter mecanisme pour enlever les '$' situés avant des quotes
//(s'il y a `$$"hola", on ne les enleve pas car on se base sur le premier '$'
//de la séquence. Ca marche en paires, donc `$$$'hola' donnera $$hola`)
char	*hd_unquote_string(char *str)
{
	int		i;
	int		j;
	char	tmp[DEF_BUF_SIZ];
	char	*ret;

	ft_bzero(tmp, DEF_BUF_SIZ);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '$')
			{
				tmp[j++] = '$';
				tmp[j++] = '$';
				i += 2;
			}
			else if (str[i + 1] == '\'' || str[i + 1] == '\"')
				i++;
		}
		if (str[i] != '\'' && str[i] != '"')
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[i] = '\0';
	ret = ft_strdup(tmp);
	if (!ret)
		return (NULL);
	return (ret);

}

char	*unquote_delimiter(char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = hd_unquote_string(str);
	// free(str);
	return (tmp);
}

void	heredoc_filler(char *delimiter, int fd, t_mo_shell *mo_shell)
{
	char	*line;
	char	*expanded_line;
	char	*tmp;
	int		i;
	bool	expand_mode;

	line = NULL;
	expanded_line = NULL;
	expand_mode = true;
	i = 0;
	while (true)
	{
		if (delimiter[i] == '\'' || delimiter[i] == '\"')
		{
			expand_mode = false;
			tmp = unquote_delimiter(delimiter);
			delimiter = tmp;
			break ;
		}
		if (!delimiter[i])
		{
			delimiter = ft_strdup(delimiter); //Pour pouvoir free simplement, sinon ca fait un double free
			break ;
		}
		i++;
	}

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(delimiter, line) == 0)
			break ;
		if (line && expand_mode == true)
		{
			expanded_line = expand_variables(line, mo_shell->shell_env, mo_shell);
			ft_putstr_fd(expanded_line, fd);
		}
		else
			ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	if (line)
		(free(line), line = NULL);
	if (expanded_line)
		(free(expanded_line), expanded_line = NULL);
	free(delimiter);
	delimiter = NULL;
}

void	heredoc_handler(t_block *nav_block, t_cmd *nav_cmd, t_mo_shell *mo_shell)
{
	char	*heredoc_name;

	(void)nav_block;
	heredoc_name = NULL;
	nav_cmd->fd_i = numerator(&heredoc_name);
	heredoc_filler(nav_block->str, nav_cmd->fd_i, mo_shell);
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
t_error	open_file_in(t_block *nav_block, t_cmd *nav_cmd, int mode, t_mo_shell *mo_shell)
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
		heredoc_handler(nav_block, nav_cmd, mo_shell);
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

t_error	open_redir_i(t_cmd **cmd_head, t_block **block_head, t_mo_shell *mo_shell)
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
			if (open_file_in(nav_block, nav_cmd, 1, mo_shell) == ERROR)
				return (ft_putstr_fd("No such file or directory\n", STDERR_FILENO), ERROR);
		}
		else if (nav_block->type == HEREDOC)
		{
			nav_block = nav_block->next;
			if (open_file_in(nav_block, nav_cmd, 2, mo_shell) == ERROR)
				return (ft_putstr_fd("No such file or directory\n", STDERR_FILENO), ERROR);
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
