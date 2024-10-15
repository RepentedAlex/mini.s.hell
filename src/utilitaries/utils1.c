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

void	ft_bzero(void *s, const size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		((char *)s)[i] = 0;
}

void	*ft_memset(void *s, const int c, const size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		((char *)s)[i] = (char)c;
	return (s);
}

void	check_in_quotes(const char c, int *quotes)
{
	if (*quotes == 0 && c == '\'')
		return (*quotes = 1, (void)1);
	if (*quotes == 0 && c == '"')
		return (*quotes = 2, (void)2);
	else if ((*quotes == 1 && c == '\'') || (*quotes == 2 && c == '"'))
		return (*quotes = 0, (void)0);
}
