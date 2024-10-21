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
#include "libft.h"

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

void	for_pipe(t_block **head, t_block **nav)
{
	int		i;
	t_block	*tmp;

	i = 0;
	tmp = block_new(ft_strdup("|"));
	tmp->type = PIPE;
	block_add_back(head, tmp);
	tmp = block_new(ft_strdup(ft_strchr((*nav)->str, '|') + 1));
	block_add_back(head, tmp);
	i = 0;
	while ((*nav)->str[i] && (*nav)->str[i] != '|')
		i++;
	(*nav)->str[i] = '\0';
	*nav = (*nav)->next;
	*nav = (*nav)->next;
}

/// @brief Takes a list of t_block and create new nodes when it finds a '|'.
/// @param head Head of the t_block list.
/// @return ERROR if an error is encountered, NO_ERROR otherwise.
t_error	split_pipes(t_block **head)
{
	t_block	*nav;

	nav = *head;
	if (!nav)
		return (ERROR);
	while (nav != NULL)
	{
		if (ft_strchr(nav->str, '|') == NULL)
		{
			nav = nav->next;
			continue ;
		}
		for_pipe(head, &nav);
	}
	return (NO_ERROR);
}
