/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:32:19 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:31:57 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks if the given node is NULL and if the return list is not NULL.
 * If the node is NULL and the return list is not NULL,
 * it clears the return list using the provided del function and returns 0.
 * If the node is NULL, it returns 0.
 * Otherwise, it returns 1.
 *
 * @param node The node to check.
 * @param ret The return list.
 * @param del The function used to delete the elements of the list.
 * @return 0 if the node is NULL and the return list is not NULL,
 * 0 if the node is NULL, 1 otherwise.
 */
static int	failure(t_list *node, t_list *ret, void (*del)(void *))
{
	if (!node && ret != NULL)
	{
		ft_lstclear(&ret, *del);
		return (0);
	}
	if (!node)
		return (0);
	return (1);
}

/**
 * Applies the function `f` to each element of the linked list `lst`
 * and creates a new list resulting from the successive applications.
 * The `del` function is used to delete the content of an element if needed.
 *
 * @param lst The pointer to the first element of the list.
 * @param f The function to apply to each element of the list.
 * @param del The function used to delete the content of an element.
 * @return The new list created by applying `f` to each element of `lst`,
 *         or NULL if an error occurred.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*ret;
	int		i;

	node = NULL;
	ret = NULL;
	if (!lst || !f || !del)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (i == 0)
		{
			ret = node;
			i = 1;
		}
		node = ft_lstnew(f(lst->content));
		if (failure(node, ret, del) == 0)
			return (NULL);
		ft_lstadd_back(&ret, node);
		lst = lst->next;
	}
	return (ret);
}
