/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:38:46 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/21 18:38:48 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_sing_redir(int *i, t_block *nav, int *value1)
{
	int	ret;

	if (nav->str[*i + 1] == '>')
	{
		ret = check_after_redir(nav->str, *i + 2);
		if (ret == 1)
			return (*value1 = 2, (true));
		if (ret == 2)
			return (*value1 = 5, (true));
		(*i)++;
	}
	else
	{
		ret = check_after_redir(nav->str, *i + 1);
		if (ret == 1)
			return (*value1 = 1, (true));
		if (ret == 2)
			return (*value1 = 5, (true));
	}
	return (false);
}

bool	check_dou_redir(int *i, t_block *nav, int *value1)
{
	int	ret;

	if (nav->str[*i + 1] == '<')
	{
		ret = check_after_redir(nav->str, *i + 2);
		if (ret == 1)
			return (*value1 = 4, true);
		if (ret == 2)
			return (*value1 = 5, true);
		(*i)++;
	}
	else
	{
		ret = check_after_redir(nav->str, *i + 1);
		if (nav->str[*i + 1] == '>')
			return (*value1 = 5, (true));
		if (ret == 1)
			return (*value1 = 3, true);
		if (ret == 2)
			return (*value1 = 5, true);
	}
	return (false);
}

int	check_redir_syntax(t_block **head)
{
	int		i;
	t_block	*nav;
	int		ret_check;

	nav = *head;
	if (!nav)
		return (ERROR);
	while (nav != NULL)
	{
		i = 0;
		while (nav->str[i])
		{
			if (nav->str[i] == '>')
				if (check_sing_redir(&i, nav, &ret_check))
					return (ret_check);
			if (nav->str[i] == '<')
				if (check_dou_redir(&i, nav, &ret_check))
					return (ret_check);
			i++;
		}
		nav = nav->next;
	}
	return (NO_ERROR);
}
