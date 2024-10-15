/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_inspection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:42:42 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/15 13:42:42 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief
/// @param head
/// @return Returns ERROR if syntax isn't correct, NO_ERROR otherwise.
t_error	check_pipes_syntax(t_block **head)
{
	int		i;
	t_block	*nav;

	//pipe + 1 != '|' -> BON
	//pipe until EOF || '|' -> exist ou != ifs -> BON

	nav = *head;
	if (!nav)
		return (ERROR);
	while (nav != NULL)
	{
		i = 0;
		while (nav->str[i])
		{
			i++;
		}
		nav = nav->next;
	}
	return (NO_ERROR);
}

/// @brief Looks for pipes.
/// @param head The head of the t_block list.
/// @return True if there is a match for a '|', false otherwise.
bool	look_for_pipes(t_block **head)
{
	t_block	*nav;

	nav = *head;
	if (nav == NULL)
		return (false);
	while (nav != NULL)
	{
		if (ft_strchr(nav->str, '|') != NULL)
			return (true);
		nav = nav->next;
	}
	return (false);
}

/// @brief Takes a list of t_block and create new nodes when it finds a '|'.
/// @param head
/// @return
t_error	split_pipes(t_block **head)
{
	if (!*head)
		return (ERROR);
	return (NO_ERROR);
}
