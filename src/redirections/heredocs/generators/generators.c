/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:57:50 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 14:58:04 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

int	gen_number(char *num, char **filename)
{
	int		fd;

	num[0] = '0';
	while (num[0] <= '9')
	{
		num[1] = '0';
		while (num[1] <= '9')
		{
			num[2] = '0';
			while (num[2] <= '9')
			{
				*filename = ft_strjoin("/tmp/heredoc", num);
				fd = open(*filename, O_RDONLY);
				if (fd == -1)
				{
					fd = open(*filename, O_RDWR | O_CREAT, 0666);
					return (free(num), fd);
				}
				(free(*filename), close(fd), fd = -1, num[2]++);
			}
			num[1]++;
		}
		num[0]++;
	}
	return (free(num), -1);
}
