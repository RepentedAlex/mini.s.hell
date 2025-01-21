/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_splitter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:19:32 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/21 15:19:50 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

#define OFFSET 0
#define QUOTE 1

t_error	split_var_space(t_block *nav, t_block **head)
{
	int		tb[2];
	char	*tmp;
	t_block	*insert;

	ft_bzero(tb, sizeof(tb));
	while (nav->str[tb[OFFSET]])
	{
		check_in_quotes(nav->str[tb[OFFSET]], &tb[QUOTE]);
		if (ft_is_ifs(nav->str[tb[OFFSET]++]) && !tb[QUOTE])
		{
			tmp = ft_strndup(nav->str, tb[OFFSET]);
			if (!tmp)
				return (ERROR);
			insert = block_new(tmp);
			tmp = (free(tmp), ft_strdup(nav->str + tb[OFFSET]));
			if (!tmp || !insert)
				return (ERROR);
			(free(nav->str), nav->str = tmp);
			block_add_front(insert, nav);
			if (nav == *head)
				*head = insert;
			tb[OFFSET] = 0;
		}
	}
	return (NO_ERROR);
}

t_error	split_blockvar_space(t_block **head)
{
	t_block	*nav;

	nav = *head;
	while (nav)
	{
		if (nav->type != RAW)
		{
			nav = nav->next;
			continue ;
		}
		if (split_var_space(nav, head) == ERROR)
			return (ERROR);
		nav = nav->next;
	}
	return (NO_ERROR);
}
