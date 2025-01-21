/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitters_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:08:00 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/30 13:59:59 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

t_error	handle_ap(t_block *nav, int *i)
{
	t_block	*tmp;
	int		j;
	char	*str_tmp;

	nav->type = APPEND;
	(*i) += 2;
	while (ft_is_ifs(nav->str[*i]))
		(*i)++;
	tmp = block_new(&nav->str[*i]);
	if (!tmp)
		return (ERROR);
	j = 0;
	while (tmp->str[j] && (!ft_is_ifs(tmp->str[j]) && tmp->str[j] != '<' && \
		tmp->str[j] != '>' && tmp->str[j] != '|'))
		j++;
	str_tmp = ft_strdup(&tmp->str[j]);
	tmp->str[j] = '\0';
	tmp->type = OUTFILE;
	block_add_after(nav, tmp);
	if (str_tmp)
		(block_add_after(tmp, block_new(str_tmp)), free(str_tmp));
	nav->str[2] = '\0';
	return (NO_ERROR);
}

int	handle_else(t_block *nav, int *i)
{
	char	*str;

	while (nav->str[*i] && nav->str[*i] != ' ' && nav->str[*i] != '\t' && \
		nav->str[*i] != '\n' && nav->str[*i] != '<' && nav->str[*i] != '>')
		(*i)++;
	if (nav->str[*i])
	{
		if (nav->str[*i] == ' ' || nav->str[*i] == '\t' || nav->str[*i] == '\n')
		{
			str = ft_strdup(&nav->str[*i + 1]);
			free(nav->str);
			nav->str = str;
		}
		else
		{
			str = ft_strdup(&nav->str[*i]);
			free(nav->str);
			nav->str = str;
		}
	}
	return (1);
}

t_error	handle_hd(t_block *nav, int *i)
{
	t_block	*tmp;
	int		j;
	char	*str_tmp;

	nav->type = HEREDOC;
	(*i) += 2;
	while (ft_is_ifs(nav->str[*i]))
		(*i)++;
	tmp = block_new(&nav->str[*i]);
	if (!tmp)
		return (ERROR);
	j = 0;
	while (tmp->str[j] && (!ft_is_ifs(tmp->str[j]) && tmp->str[j] != '<' && \
		tmp->str[j] != '>' && tmp->str[j] != '|'))
		j++;
	str_tmp = ft_strdup(&tmp->str[j]);
	tmp->str[j] = '\0';
	tmp->type = EOFHD;
	block_add_after(nav, tmp);
	if (str_tmp)
		(block_add_after(tmp, block_new(str_tmp)), free(str_tmp));
	nav->str[2] = '\0';
	return (NO_ERROR);
}

int	handle_ifs(t_block *nav, int *i)
{
	t_block	*tmp;

	tmp = block_new(&nav->str[*i]);
	tmp->type = RAW;
	block_add_after(nav, tmp);
	*i = 0;
	while (nav->str[*i] && nav->str[*i] != ' ' && nav->str[*i] != '\t' && \
		nav->str[*i] != '\n' && nav->str[*i] != '<' && nav->str[*i] != '>')
		(*i)++;
	nav->str[*i] = '\0';
	return (1);
}

int	handle_ri(t_block *nav, int *i)
{
	t_block	*tmp;
	int		j;
	char	*str_tmp;

	nav->type = REDIR_I;
	(*i) += 1;
	while (ft_is_ifs(nav->str[*i]))
		(*i)++;
	tmp = block_new(&nav->str[*i]);
	if (!tmp)
		return (ERROR);
	j = 0;
	while (tmp->str[j] && (!ft_is_ifs(tmp->str[j]) && tmp->str[j] != '<' && \
		tmp->str[j] != '>' && tmp->str[j] != '|'))
		j++;
	str_tmp = ft_strdup(&tmp->str[j]);
	tmp->str[j] = '\0';
	tmp->type = INFILE;
	block_add_after(nav, tmp);
	if (str_tmp)
		(block_add_after(tmp, block_new(str_tmp)), free(str_tmp));
	nav->str[1] = '\0';
	return (NO_ERROR);
}
