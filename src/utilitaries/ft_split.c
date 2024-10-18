/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:36:32 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/15 14:36:35 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void block_string_tidyer(t_block **head)
{
	t_block	*nav;
	char	*tmp;

	nav = *head;
	if (!nav)
		return;
	while (nav)
	{
		tmp = string_tidyer(nav->str);
		if (tmp != NULL)
		{
			free(nav->str);
			nav->str = tmp;
		}
		tmp = NULL;
		nav = nav->next;
	}
}
