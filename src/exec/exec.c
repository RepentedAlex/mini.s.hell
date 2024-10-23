/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:39:02 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/23 18:39:05 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cl(t_block **head)
{
	t_block	*nav;

	nav = *head;
	if (!nav)
		return ;
	while (nav)
		nav = nav->next;
	//TODO Setup pipes and redirections from right to left, redirections steal the pipe

	nav = *head;
	//TODO Execute from left to right
	while (nav)
	{
		if (is_builtin(nav->str) == true)
		{
			//exec builtin
			launch_builtins(nav);
		}
		else
		{
			//execve
		}
		nav = nav->next;
	}
}
