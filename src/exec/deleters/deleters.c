/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:09:07 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/21 17:09:09 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "minishell.h"

void	unlink_heredocs(void)
{
	char	*filename;
	char	num[4];

	num[3] = '\0';
	num[0] = '0';
	while (num[0] <= '9')
	{
		num[1] = '0';
		while (num[1] <= '9')
		{
			num[2] = '0';
			while (num[2] <= '9')
			while (num[2] <= '9')
			{
				filename = ft_strjoin("/tmp/heredoc", num);
				//PUT CODE HERE
				unlink(filename);
				(free(filename), filename = NULL);
				num[2]++;
			}
			num[1]++;
		}
		num[0]++;
	}
}
