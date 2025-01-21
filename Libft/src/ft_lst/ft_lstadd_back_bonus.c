/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:30:51 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:02:41 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Adds a new element to the end of a linked list.
 *
 * @param lst The address of a pointer to the first element of the list.
 * @param new The element to add to the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tail;

	tail = ft_lstlast(*lst);
	if (*lst == NULL)
		*lst = new;
	else
		tail->next = new;
}
