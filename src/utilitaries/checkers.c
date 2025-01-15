/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:35:25 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 13:35:29 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	words_in_str(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == ':' && flag == 0)
			flag = 1;
		else if (str[i] == ':' && flag == 1)
			return (true);
		if (str[i] != ':')
			return (true);
		i++;
	}
	return (false);
}
