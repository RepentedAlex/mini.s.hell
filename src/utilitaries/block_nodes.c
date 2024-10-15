/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:26:20 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/15 17:26:35 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	block_add_back(t_block **head, t_block *node)
{
	t_block	*tail;

	tail = block_goto_last(*head);
	if (tail == NULL)
		*head = node;
	else
	{
		tail->next = node;
		node->prev = tail;
	}
	return (NO_ERROR);
}

t_error	block_add_front(t_block **head, t_block *node)
{
	t_block	*nav;

	if (*head == NULL)
		*head = node;
	else
	{
		nav = *head;
		nav->prev = node;
		node->next = nav;
		node->prev = NULL;
	}
	return (NO_ERROR);
}

t_block	*block_goto_last(t_block *head)
{
	t_block	*nav;

	nav = head;
	if (nav == NULL)
		return (NULL);
	while (nav->next)
		nav = nav->next;
	return (nav);
}

t_block	*block_new(char *str)
{
	t_block	*node;

	node = (t_block *)malloc(sizeof(t_block));
	if (!node)
		return (NULL);
	node->str = str;
	node->next = NULL;
	node->prev = NULL;
	node->type = 0;
	return (node);
}




