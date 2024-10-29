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

void	block_pop(t_block **block)
{
	t_block	*tmp;
	t_block	*save_prev;
	t_block	*save_next;

	tmp = *block;
	save_prev = tmp->prev;
	save_next = tmp->next;
	if (tmp->str)
	{
		free(tmp->str);
		tmp->str = NULL;
	}
	tmp->prev->next = save_next;
	if (tmp->next)
		tmp->next->prev = save_prev;
	free(tmp);
}

t_error	block_add_before(t_block *ref, t_block *to_insert)
{
	t_block	*tmp;

	if (ref == NULL)
		ref = to_insert;
	else
	{
		tmp = ref->prev;
		tmp->next = to_insert;
		to_insert->prev = tmp;
		ref->prev = to_insert;
		to_insert->next = ref;
	}
	return (NO_ERROR);
}

t_error	block_add_after(t_block *ref, t_block *to_insert)
{
	t_block	*tmp;

	if (ref == NULL)
		ref = to_insert;
	else
	{
		tmp = ref->next;
		to_insert->next = tmp;
		to_insert->prev = ref;
		ref->next = to_insert;
	}
	return (NO_ERROR);
}

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
