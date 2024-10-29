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

t_error	check_redir_o(int *i, t_block *nav, int *value1)
{
	int	ret;

	if (nav->str[*i + 1] == '>')
	{
		ret = check_after_redir(nav->str, *i + 2);
		if (ret == 1)
			return (*value1 = 2, ERROR);
		if (ret == 2)
			return (*value1 = 5, ERROR);
		(*i)++;
	}
	else
	{
		ret = check_after_redir(nav->str, *i + 1);
		if (ret == 1)
			return (*value1 = 1, ERROR);
		if (ret == 2)
			return (*value1 = 5, ERROR);
	}
	return (NO_ERROR);
}

t_error	check_redir_i(int *i, t_block *nav, int *value1)
{
	int	ret;

	if (nav->str[*i + 1] == '<')
	{
		ret = check_after_redir(nav->str, *i + 2);
		if (ret == 1)
			return (*value1 = 4, ERROR);
		if (ret == 2)
			return (*value1 = 5, ERROR);
		(*i)++;
	}
	else
	{
		ret = check_after_redir(nav->str, *i + 1);
		if (nav->str[*i + 1] == '>')
			return (*value1 = 5, ERROR);
		if (ret == 1)
			return (*value1 = 3, ERROR);
		if (ret == 2)
			return (*value1 = 5, ERROR);
	}
	return (NO_ERROR);
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
				if (check_redir_o(&i, nav, &ret_check) == ERROR)
					return (ret_check);
			if (nav->str[i] == '<')
				if (check_redir_i(&i, nav, &ret_check))
					return (ret_check);
			i++;
		}
		nav = nav->next;
	}
	return (NO_ERROR);
}
