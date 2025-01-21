/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:30:55 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:25:15 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a string to an integer.
 *
 * This function converts the initial portion of the string pointed to by `nptr`
 * to its equivalent integer representation. It skips leading white spaces and
 * handles optional sign characters. The conversion stops when it encounters an
 * invalid character or the end of the string.
 *
 * @param nptr The string to be converted.
 * @return The converted integer value.
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	output;
	int	sign;

	i = 0;
	output = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] <= 13)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
		{
			sign *= (-1);
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		output = output * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * output);
}
