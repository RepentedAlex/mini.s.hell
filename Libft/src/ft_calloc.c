/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:56:40 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:23:25 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates memory for an array of elements and initializes them to 0.
 *
 * @param nmemb The number of elements to allocate memory for.
 * @param size The size of each element.
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pointer;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (size > __SIZE_MAX__ / nmemb)
		return (NULL);
	pointer = NULL;
	pointer = malloc(nmemb * size);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, nmemb * size);
	return (pointer);
}
