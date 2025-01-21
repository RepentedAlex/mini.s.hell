/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:33:37 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:03:37 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns the last element of a linked list.
 *
 * @param lst The pointer to the head of the linked list.
 * @return The pointer to the last element of the linked list.
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last_el;

	last_el = lst;
	if (lst == NULL)
		return (NULL);
	while (last_el->next != NULL)
	{
		last_el = last_el->next;
	}
	return (last_el);
}
