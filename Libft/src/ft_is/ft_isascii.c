/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:00:05 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:32:47 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks whether the given character is a valid ASCII character.
 *
 * This function checks if the ASCII
 * value of the character falls within the range of 0 to 127,
 * which represents the valid ASCII character set.
 *
 * @param c The character to be checked.
 * @return 1 if the character is a valid ASCII character, 0 otherwise.
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
