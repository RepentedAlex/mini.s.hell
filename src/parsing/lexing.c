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

void	identify_tokens(t_token **head)
{
	t_token	*nav;

	nav = *head;
	if (!nav)
		return ;
	while (nav)
	{
		if (ft_strncmp(nav->str, "|", 1) == 0)
			nav->type = PIPE;
		if (ft_strncmp(nav->str, "<", 1) == 0)
			nav->type = REDIR_I;
		if (ft_strncmp(nav->str, ">", 1) == 0)
			nav->type = REDIR_O;
		if (ft_strncmp(nav->str, ">>", 2) == 0)
			nav->type = APPEND;
		if (ft_strncmp(nav->str, "<<", 2) == 0)
			nav->type = HEREDOC;
		nav = nav->next;
	}
}
