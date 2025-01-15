/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:49:54 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/21 18:49:56 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

bool	check_after_pipe(char *str, int i)
{
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	check_before_pipe(char *str, int i)
{
	while (i >= 0 && str[i] != '|')
	{
		if (ft_isalpha(str[i]))
			return (true);
		i--;
	}
	return (false);
}

/// @brief Check if all pipes' syntax is correct
/// @param head Head of the t_block list.
/// @return Returns ERROR if syntax isn't correct, NO_ERROR otherwise.
t_error	check_pipes_syntax(t_block **head)
{
	int		i;
	t_block	*nav;

	nav = *head;
	if (!nav)
		return (ERROR);
	while (nav != NULL)
	{
		i = 0;
		while (nav->str[i])
		{
			if (nav->str[i] == '|')
			{
				if (check_before_pipe(nav->str, i - 1) == false)
					return (ERROR);
				if (check_after_pipe(nav->str, i + 1) == false)
					return (ERROR);
			}
			i++;
		}
		nav = nav->next;
	}
	return (NO_ERROR);
}
