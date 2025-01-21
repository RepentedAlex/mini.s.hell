/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:00:10 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:29:39 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prints a single character to the specified file descriptor.
 *
 * This function writes a single character to the specified file descriptor.
 *
 * @param c The character to be printed.
 * @param fd The file descriptor to write the character to.
 */
static void	ft_printnum_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/**
 * Writes the integer 'n' to the file descriptor 'fd'.
 * 
 * If 'n' is equal to -2147483648,
 * the function writes the string "-2147483648" to 'fd'.
 * 
 * If 'n' is between 0 and 9 (inclusive),
 * the function writes the character representation of 'n' to 'fd'.
 * 
 * If 'n' is negative, the function writes a '-' character to 'fd',
 * followed by the absolute value of 'n'.
 * 
 * If 'n' is positive and greater than 9,
 * the function recursively writes the digits of 'n' to 'fd'.
 * 
 * @param n The integer to be written to 'fd'.
 * @param fd The file descriptor to write to.
 */
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n >= 0 && n <= 9)
	{
		ft_printnum_fd(n + '0', fd);
	}
	else if (n < 0)
	{
		ft_printnum_fd('-', fd);
		ft_putnbr_fd(n * -1, fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
