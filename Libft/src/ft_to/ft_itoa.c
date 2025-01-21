/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:08:39 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:24:53 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Calculates the length of an integer number.
 *
 * This function calculates the length of an integer number\
 * by counting the number of digits in it.
 * It takes a long integer as input and returns the length of the number.
 * The length includes the negative sign if the number is negative.
 *
 * @param n The integer number to calculate the length of.
 * @return The length of the integer number.
 */
static int	ft_get_nb_len(long int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

/**\
 * @brief Transcribes a number into a character array.
 *
 * This function transcribes a given number `n`
 * into a character array `dst` of length `len`.
 * The resulting character array is null-terminated.
 *
 * @param dst The destination character array to store the transcribed number.
 * @param n The number to be transcribed.
 * @param len The length of the destination character array.
 *
 * @return The transcribed number as an unsigned character array.
 */
static void	ft_transcribe_nb(char *dst, long int n, int len)
{
	dst[len] = '\0';
	len--;
	if (n == 0)
	{
		dst[len] = '\0';
		return ;
	}
	while (n > 0 && len >= 0)
	{
		dst[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
}

/**
 * Converts an integer to a string representation.
 *
 * @param n The integer to be converted.
 * @return A pointer to the string representation of the integer.
 *         Returns NULL if memory allocation fails.
 */
char	*ft_itoa(int n)
{
	char	*ascii;
	int		n_len;
	long	n_long;

	n_long = n;
	n_len = ft_get_nb_len(n_long);
	ascii = (char *)malloc(sizeof(char) * (n_len + 1));
	if (!ascii)
		return (NULL);
	if (n_long < 0)
	{
		ascii[0] = '-';
		n_long = -n_long;
	}
	else if (n_long == 0)
	{
		ascii[0] = '0';
		ascii[1] = '\0';
		return (ascii);
	}
	ft_transcribe_nb(ascii, n_long, n_len);
	return (ascii);
}
