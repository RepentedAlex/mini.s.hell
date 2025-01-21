/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:31:40 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:03:18 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Deletes a single node from a linked list.
 *
 * This function deletes the given node `lst` from the linked list. The `del`
 * function is called to free the memory allocated for the content of the node.
 *
 * @param lst The node to be deleted.
 * @param del The function used to delete the content of the node.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
