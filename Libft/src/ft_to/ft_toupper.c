/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:46:41 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:25:24 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Converts a lowercase letter to its corresponding uppercase letter.
 *
 * @param c The character to be converted.
 * @return The uppercase version of the character if it is a lowercase letter,
 *         otherwise returns the character unchanged.
 */
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c -= 32);
	else
		return (c);
}
