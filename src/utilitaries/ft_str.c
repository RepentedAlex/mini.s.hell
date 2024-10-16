/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:14:20 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/15 12:14:24 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		result;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
		{
			result = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
			return (result);
		}
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, const size_t n)
{
	size_t	i;
	int		result;

	if (!s1 || !s2)
		return (-1);
	if (n == 0)
		return (0);
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
		{
			result = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
			return (result);
		}
		i++;
	}
	return (0);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, const int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

int	count_following_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_ifs(str[i]))
	{
		i++;
	}
	return (i);
}

int get_num_unnec_spaces(char *s)
{
	int		i;
	int		spaces_to_remove;
	int		quotes;
	spaces_to_remove = 0;
	quotes = 0;
	i = 0;
	while (s[i])
	{
		check_in_quotes(s[i], &quotes);
		if (!quotes && ft_strchr(IFS, s[i]))
		{
			spaces_to_remove += count_following_spaces(&s[i + 1]);
			i += count_following_spaces(&s[i + 1]);
		}
		i++;
	}
	return (spaces_to_remove);
}

char	*string_tidyer(char *s)
{
	char	*ret;
	int		unnecessary_spaces;
	int		i;
	int		j;
	int		quotes;

	ret = NULL;
	(void)ret;
	unnecessary_spaces = get_num_unnec_spaces(s);
	ret = (char *)malloc(sizeof(char) * ((ft_strlen(s) - unnecessary_spaces) + 1));
	if (!ret)
		return (NULL);
	//COPIER STRING EN ENLEVANT ESPACES SUPERFLUS
	quotes = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		check_in_quotes(s[i], &quotes);
		if (!quotes && ft_is_ifs(s[i]))
		{
			ret[j++] = s[i];
			while (ft_is_ifs(s[i]))
				i++;
			continue ;
		}
		ret[j] = s[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
