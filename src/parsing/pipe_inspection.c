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

t_error	check_pipes_syntax(t_block **head)
{
	(void)head;
	return (ERROR);
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
