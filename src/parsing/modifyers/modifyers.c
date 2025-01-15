/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifyers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:44:52 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 15:45:08 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

t_error	new_expand_variables(t_block **head, t_mo_shell *mo_shell)
{
	t_block	*nav;
	char	*tmp;

	nav = *head;
	while (nav)
	{
		if (nav->type != EOFHD)
		{
			tmp = expand_variables(nav->str, mo_shell);
			if (!tmp)
				return (ERROR);
			free(nav->str);
			nav->str = tmp;
		}
		nav = nav->next;
	}
	return (NO_ERROR);
}

static void	quotes_handler(char c, int *quotes)
{
	if (*quotes == 1 && c == '\'')
		*quotes = 0;
	else if (*quotes == 2 && c == '\"')
		*quotes = 0;
	else if (*quotes == 0)
	{
		if (c == '\'')
			*quotes = 1;
		else if (c == '\"')
			*quotes = 2;
	}
}

static int	should_copy_char(char c, int quotes)
{
	if (!quotes)
		return (1);
	if ((quotes == 1 && c != '\'') || (quotes == 2 && c != '\"'))
		return (1);
	return (0);
}

char	*unquote_string(char *str)
{
	int		i;
	int		j;
	int		quotes;
	char	tmp[DEF_BUF_SIZ];
	char	*ret;

	i = 0;
	j = 0;
	quotes = 0;
	while (str[i])
	{
		if ((quotes == 1 && str[i] == '\'') || (quotes == 2 && str[i] == '\"'))
		{
			quotes_handler(str[i], &quotes);
			i++;
			continue ;
		}
		quotes_handler(str[i], &quotes);
		if (should_copy_char(str[i], quotes))
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	ret = ft_strdup(tmp);
	return (ret);
}
