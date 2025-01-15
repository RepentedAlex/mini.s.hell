/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifyers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:17:15 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 15:17:18 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

t_error	expand_cmd_path(t_cmd **head, char *envp[])
{
	t_cmd	*nav;
	char	*tmp;

	nav = *head;
	while (nav)
	{
		if (is_builtin(nav->cmd) == true)
		{
			nav = nav->next;
			continue ;
		}
		if (ft_strncmp(nav->cmd, "./", 2) == 0 || ft_strchr(nav->cmd, \
			'/') != NULL || \
			is_builtin(nav->cmd))
			nav = nav->next;
		else
		{
			tmp = get_path(nav->cmd, envp);
			if (!tmp)
				return (ERROR);
			(free(nav->cmd), nav->cmd = tmp, tmp = NULL);
			nav = nav->next;
		}
	}
	return (NO_ERROR);
}
