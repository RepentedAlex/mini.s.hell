/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:51:38 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/08 18:51:41 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(const char *str)
{
	int		i;
	int		ret;
	bool	in_word;

	i = 0;
	ret = 0;
	in_word = false;
	while (str[i])
	{
		if (!is_ifs(str[i]) && !in_word)
		{
			in_word = true;
			ret++;
		}
		else if (is_ifs(str[i]) && in_word)
			in_word = false;
		i++;
	}
	return (ret);
}

int	count_leading_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!isspace(str[i]))
			break ;
		i++;
	}
	return (i);
}

void	split_str(char *str, char **ret, int *nb_token, bool *in_word)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str && i >= 0)
	{
		if (i == 0 && !is_ifs(str[(i)]))
		{
			ret[(*nb_token)] = &str[(i)];
			(*nb_token)--;
		}
		if (!is_ifs(str[(i)]) && !*in_word)
			*in_word = true;
		else if (is_ifs(str[(i)]) && *in_word)
		{
			ret[(*nb_token)] = &str[i + 1];
			(*nb_token)--;
			*in_word = false;
		}
		if (is_ifs(str[(i)]))
			str[(i)] = '\0';
		(i)--;
	}
}
