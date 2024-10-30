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

#include "minishell.h"

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

	while (nav->str[*i] && nav->str[*i] != '>' && nav->str[*i] != '<' && \
		nav->str[*i] != '|' && !ft_is_ifs(nav->str[*i]))
		(*i)++;
	if (ft_is_ifs(nav->str[*i]))
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
