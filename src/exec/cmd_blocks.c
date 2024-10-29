/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_blocks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:01:18 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/24 16:01:21 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_cmd	*cmd_new(char *str)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd = ft_strdup(str);
	node->args = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->fd_i = -2;
	node->fd_o = -2;
	return (node);
}

t_error	cmd_add_back(t_cmd **head, t_cmd *node)
{
	t_cmd	*tail;

	tail = cmd_goto_last(*head);
	if (tail == NULL)
		*head = node;
	else
	{
		tail->next = node;
		node->prev = tail;
	}
	return (NO_ERROR);
}

t_error	cmd_add_after(t_cmd *ref, t_cmd *to_insert)
{
	t_cmd	*tmp;

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

t_cmd	*cmd_goto_last(t_cmd *head)
{
	t_cmd	*nav;

	nav = head;
	if (nav == NULL)
		return (NULL);
	while (nav->next)
		nav = nav->next;
	return (nav);
}
