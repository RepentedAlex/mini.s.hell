/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:50:00 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:31:03 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates a new list node with the given content.
 *
 * @param content The content to be stored in the new node.
 * @return A pointer to the newly created list node.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(1 * sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
