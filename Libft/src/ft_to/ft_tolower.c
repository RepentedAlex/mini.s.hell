/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:54:13 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:25:35 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Converts an uppercase letter to its lowercase equivalent.
 *
 * @param c The character to be converted.
 * @return The lowercase equivalent of the input character,
 * if it is an uppercase letter.
 *         Otherwise, returns the input character unchanged.
 */
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c += 32);
	else
		return (c);
}
