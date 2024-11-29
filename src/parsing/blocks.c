/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:22:22 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/29 16:14:56 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_block	*block_setup_first(t_mo_shell *mo_shell)
{
	t_block	*block;

	block = malloc(sizeof(t_block));
	if (!block)
		return (NULL);
	block->str = ft_strdup(mo_shell->expanded_input);
	if (!block->str)
		return (NULL);
	block->next = NULL;
	block->prev = NULL;
	block->type = 0;
	return (block);
}

void	for_space(t_block *nav)
{
	int		i;

	i = 0;
	while (nav->str[i])
	{
		// if ((nav->str[i] == '\'' || nav->str[i] == '"') && handle_quotes(nav, &i))
		// 	break ;
		if (!ft_is_symbol(&nav->str[i]) && handle_no_symbols_no_ifs(nav, &i))
			break ;
		if (!ft_strncmp(&nav->str[i], "<<", 2) && handle_hd(nav, &i))
			break ;
		if (!ft_strncmp(&nav->str[i], ">>", 2) && handle_ap(nav, &i))
			break ;
		if (!ft_strncmp(&nav->str[i], "<", 1) && handle_ri(nav, &i))
			break ;
		if (!ft_strncmp(&nav->str[i], ">", 1) && handle_ro(nav, &i))
			break ;
		if (!ft_is_ifs(nav->str[i]) && handle_ifs(nav, &i))
			break ;
		if (handle_else(nav, &i))
			continue ;
		i++;
	}
}

t_error	split_spaces(t_block **head)
{
	t_block	*nav;

	nav = *head;
	if (!nav)
		return (ERROR);
	while (nav)
	{
		if (nav->type == RAW)
			for_space(nav);
		nav = nav->next;
	}
	return (NO_ERROR);
}
