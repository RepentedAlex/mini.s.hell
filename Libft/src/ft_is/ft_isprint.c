/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:07:30 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:32:30 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks if a character is a printable character.
 *
 * A character is considered printable
 * if its ASCII value is between 32 and 126 (inclusive).
 *
 * @param c The character to be checked.
 * @return 1 if the character is printable, 0 otherwise.
 */
int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (c);
	else
		return (0);
}
