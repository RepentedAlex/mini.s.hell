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

bool	check_after_pipe(char *str, int i)
{
	while (str[i])
	{
		if (ft_is_alpha(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	check_before_pipe(char *str, int i)
{
	while (i >= 0 && str[i] != '|')
	{
		if (ft_is_alpha(str[i]))
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
			if (nav->str[i] == '|')
			{
				// Check word.s before pipe
				if (check_before_pipe(nav->str, i - 1) == false)
					return (ERROR);
				// Check word.s after pipe
				if (check_after_pipe(nav->str, i + 1) == false)
					return (ERROR);
			}
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
/// @param head Head of the t_block list.
/// @return ERROR if an error is encountered, NO_ERROR otherwise.
t_error	split_pipes(t_block **head)
{
	t_block	*nav;
	t_block	*tmp;
	int		i;

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
		tmp = block_new("|");
		tmp->type = PIPE;
		block_add_back(head, tmp);
		tmp = block_new(strdup(ft_strchr(nav->str, '|') + 1));	//TODO ft_strdup
		block_add_back(head, tmp);
		i = 0;
		while (nav->str[i] && nav->str[i] != '|')
			i++;
		nav->str[i] = '\0';
		nav = nav->next;
		nav = nav->next;
	}
	return (NO_ERROR);
}
