/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:22:22 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/15 13:22:25 by apetitco         ###   ########.fr       */
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
	free(mo_shell->expanded_input);
	mo_shell->expanded_input = NULL;
	return (block);
}

t_error	split_spaces(t_block **head)
{
	t_block	*nav;
	t_block	*tmp;
	// char	*strchr_tmp;
	int		i;
	int		quotes;

	// strchr_tmp = NULL;
	quotes = 0;
	nav = *head;
	if (!nav)
		return (ERROR);
	while (nav != NULL)
	{
		if (!ft_string_is_ifs(nav->str))
		{
			nav = nav->next;
			continue ;
		}
		i = 0;
		while (nav->str[i])
		{
			check_in_quotes(nav->str[i], &quotes);
			if (!quotes && ft_is_ifs(nav->str[i]))
			{
				tmp = block_new(&nav->str[i + 1]);
				tmp->type = RAW;
				block_add_after(nav, tmp);
				i = 0;
				while (nav->str[i] && nav->str[i] != ' ' && nav->str[i] != '\t' && nav->str[i] != '\n')
					i++;
				nav->str[i] = '\0';
				break ;
			}
			i++;
		}
		nav = nav->next;
	}
	return (NO_ERROR);
}
