/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:31:29 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:32:19 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Clears a linked list by deleting all
 * of its nodes and freeing the memory.
 *
 * This function clears a linked list by deleting
 * all of its nodes and freeing the memory
 * occupied by each node. It takes a double pointer
 * to the head of the list and a function
 * pointer to the function used to delete the content of each node.
 *
 * @param lst A pointer to the pointer to the head of the list.
 * @param del The function used to delete the content of each node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	temp = NULL;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, *del);
		*lst = temp;
	}
}
