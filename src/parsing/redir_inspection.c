/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_inspection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:49:50 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/15 13:49:53 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	check_redir_syntax(t_block **head)
{
	(void)head;
	return (ERROR);
}

bool	look_for_redir(t_block **head)
{
	(void)head;
	return (true);
}

/// @brief Takes a list of t_block and create new nodes when it finds a '<', '<<', '>', '>>'.
/// @param head
/// @return
t_error	split_redir(t_block **head)
{
	if (!*head)
		return (ERROR);
	return (NO_ERROR);
}
