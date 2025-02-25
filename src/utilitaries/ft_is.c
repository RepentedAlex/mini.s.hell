/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:05:36 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/11 13:05:39 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief
/// @param c
/// @return
bool	ft_is_ifs(const char c)
{
	int	i;

	i = -1;
	while (IFS[++i])
		if (IFS[i] == c)
			return (true);
	return (false);
}

bool	ft_string_is_ifs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_ifs(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	ft_string_is_only_ifs(char *str)
{
	int		i;

	i = 0;
	while (ft_is_ifs(str[i]))
		i++;
	if (!str[i])
		return (true);
	return (false);
}

//apetitco :
// On peut sûrement tirer parti de l'enum t_lexcat pour identifier le symbole
//plus précisément lorsque l'on retourne.
int	ft_is_symbol(const char *str)
{
	int	i;

	i = -1;
	while (str[++i] && i < 2)
	{
		if (str[i] == '|')
			return (1);
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				return (2);
			return (1);
		}
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				return (2);
			return (1);
		}
	}
	return (0);
}
