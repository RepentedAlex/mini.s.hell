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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, const size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && i < n)
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

void	check_in_quotes(const char c, int *quotes)
{
	if (*quotes == 0 && c == '\'')
		*quotes = 1;
	if (*quotes == 0 && c == '"')
		*quotes = 2;
	else if ((*quotes == 1 && c == '\'') || (*quotes == 2 && c == '"'))
		*quotes = 0;
}
