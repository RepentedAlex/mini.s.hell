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
#include "libft.h"

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

int	get_num_unnec_spaces(char *s)
{
	int		i;
	int		spaces_to_remove;
	int		quotes;

	spaces_to_remove = 0;
	quotes = 0;
	i = -1;
	while (ft_is_ifs(s[++i]))
		spaces_to_remove++;
	if (!s[i])
		return (i);
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
	while (ft_is_ifs(s[--i]))
		spaces_to_remove++;
	return (spaces_to_remove);
}

bool	check_words_after(char *s)
{
	int		i;

	i = 0;
	while (s[i] && ft_is_ifs(s[i]))
		i++;
	if (s[i] == '\0')
		return (false);
	return (true);
}

void	remove_space(char *s, char *ret, int *j, int quotes)
{
	int		i;

	i = 0;
	while (ft_is_ifs(s[i]))
	{
		check_in_quotes(s[i], &quotes);
		if (!quotes)
			i++;
	}
	while (s[(i)])
	{
		check_in_quotes(s[(i)], &quotes);
		if (!quotes && ft_is_ifs(s[(i)]))
		{
			ret[(*j)++] = s[(i)];
			while (ft_is_ifs(s[(i)]))
				(i)++;
			continue ;
		}
		ret[(*j)] = s[(i)];
		(i)++;
		(*j)++;
		if (check_words_after(&s[(i)]) == false)
			break ;
	}
}

char	*string_tidyer(char *s)
{
	char	*ret;
	int		unnecessary_spaces;
	int		j;
	int		quotes;

	ret = NULL;
	(void)ret;
	unnecessary_spaces = get_num_unnec_spaces(s);
	if (unnecessary_spaces == 0)
		return (ft_strdup(s));
	if (ft_strlen(s) - unnecessary_spaces == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * ((ft_strlen(s) - \
		unnecessary_spaces) + 1));
	if (!ret)
		return (NULL);
	quotes = 0;
	j = 0;
	remove_space(s, ret, &j, quotes);
	ret[j] = '\0';
	return (ret);
}
