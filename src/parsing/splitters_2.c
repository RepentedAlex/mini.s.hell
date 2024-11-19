/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitters_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:59:24 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/30 13:59:28 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "minishell.h"

int	handle_quotes(t_block *nav, int *i)
{
	int		quotes;
	t_block	*tmp;
	char	*str_tmp;
	int		j;

	quotes = 0;
	if (nav->str[*i] == '\'')
		quotes = 1;
	else if (nav->str[*i] == '\"')
		quotes = 2;
	str_tmp = ft_strdup(&nav->str[*i + 1]);
	free(nav->str);
	nav->str = str_tmp;
	while ((quotes == 1 && nav->str[*i] != '\'') || \
		(quotes == 2 && nav->str[*i] != '\"'))
		(*i)++;
	j = 1;
	while (ft_is_ifs(nav->str[*i + j]) && !ft_is_symbol(&nav->str[*i + j]) && \
		nav->str[*i + j] != '\'' && nav->str[*i + j] != '\"')
		j++;
	tmp = block_new(&nav->str[*i + j]);
	nav->str[*i] = '\0';
	block_add_after(nav, tmp);
	return (1);
}

int	handle_ro(t_block *nav, int *i)
{
	t_block	*tmp;

	nav->type = REDIR_O;
	tmp = block_new(&nav->str[1]);
	tmp->type = OUTFILE;
	block_add_after(nav, tmp);
	*i = 1;
	while (nav->str[*i] && nav->str[*i] != ' ' && nav->str[*i] != '\t' && \
		nav->str[*i] != '\n' && nav->str[*i] != '<' && nav->str[*i] != '>')
		(*i)++;
	if (nav->str[*i])
	{
		tmp = block_new(&nav->str[*i]);
		tmp->type = RAW;
		block_add_after(nav->next, tmp);
		nav->str[1] = '\0';
		nav->next->str[*i - 1] = '\0';
	}
	nav->str[1] = '\0';
	return (1);
}

int	handle_no_symbols_no_ifs(t_block *nav, int *i)
{
	t_block	*tmp;
	int		quotes;

	quotes = 0;
	while ((nav->str[*i] && nav->str[*i] != '>' && nav->str[*i] != '<' && \
		nav->str[*i] != '|' && !ft_is_ifs(nav->str[*i])) || (quotes && ft_is_ifs(nav->str[*i])))
	{
		check_in_quotes(nav->str[*i], &quotes);
		(*i)++;
	}
	if (!quotes && ft_is_ifs(nav->str[*i]))
	{
		nav->str[*i] = '\0';
		(*i)++;
		while (nav->str[*i] && ft_is_ifs(nav->str[*i]))
			(*i)++;
		tmp = block_new(&nav->str[*i]);
		block_add_after(nav, tmp);
	}
	else if (nav->str[*i] == '>' || nav->str[*i] == '<')
	{
		tmp = block_new(&nav->str[*i]);
		block_add_after(nav, tmp);
		nav->str[*i] = '\0';
	}
	return (1);
}
