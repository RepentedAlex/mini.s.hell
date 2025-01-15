/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:47:55 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/20 14:06:21 by llabonde         ###   ########.fr       */
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
	fd = gen_number(num, filename);
	if (fd == -1)
		return (free(num), -1);
	return (fd);
}

void	hdus_handle_dollar(char *str, char *tmp, int *i, int *j)
{
	if (str[(*i) + 1] == '$')
	{
		tmp[(*j)++] = '$';
		tmp[(*j)++] = '$';
		(*i) += 2;
	}
	else if (str[(*i) + 1] == '\'' || str[(*i) + 1] == '\"')
		(*i)++;
}

void	handle_unquote_delim(char **delimiter, bool *expand_mode)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (true)
	{
		if ((*delimiter)[i] == '\'' || (*delimiter)[i] == '\"')
		{
			*expand_mode = false;
			tmp = unquote_delimiter(*delimiter);
			*delimiter = tmp;
			break ;
		}
		if (!(*delimiter)[i])
		{
			*delimiter = ft_strdup(*delimiter);
			break ;
		}
		i++;
	}
}

void	heredoc_filler(char *delimiter, int fd, t_mo_shell *mo_shell)
{
	char	*line;
	char	*expanded_line;
	bool	expand_mode;

	line = NULL;
	expanded_line = NULL;
	expand_mode = true;
	handle_unquote_delim(&delimiter, &expand_mode);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(delimiter, line) == 0)
			break ;
		if (line && expand_mode == true)
			expand_hd_i(fd, mo_shell, line, &expanded_line);
		else
			ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	if (line)
		(free(line), line = NULL);
	free(delimiter);
	delimiter = NULL;
}

void	heredoc_handler(t_block *nav_block, t_cmd *nav_cmd, t_mo_shell \
	*mo_shell)
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
