/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:38:11 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/08 18:38:13 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_ifs(const char c)
{
	int	i;

	i = -1;
	while (IFS[++i])
		if (IFS[i] == c)
			return (true);
	return (false);
}

int	strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

void	trim_leading_whitespace(char *str, const int leading_whitespaces)
{
	int	i;

	i = 0;
	while (is_ifs(str[i]))
		i++;
	while (str[i])
	{
		str[i - leading_whitespaces] = str[i];
		i++;
	}
	str[i - leading_whitespaces] = '\0';
}
