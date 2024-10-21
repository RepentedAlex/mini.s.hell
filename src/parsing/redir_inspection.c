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
#include "libft.h"

bool	check_after_redir(char *str, int i)
{
	while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|')
	{
		if (ft_is_alpha(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	check_before_redir(char *str, int i)
{
	while (i >= 0 && str[i] != '<' && str[i] != '>' && str[i] != '|')
	{
		if (ft_is_alpha(str[i]))
			return (true);
		i--;
	}
	return (false);
}

bool	look_for_redir(t_block **head)
{
	t_block	*nav;

	nav = *head;
	if (nav == NULL)
		return (false);
	while (nav != NULL)
	{
		if (ft_strchr(nav->str, '<') || ft_strchr(nav->str, '>'))
			return (true);
		nav = nav->next;
	}
	return (false);
}
