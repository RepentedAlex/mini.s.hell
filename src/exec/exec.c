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

void	execute_cl(t_mo_shell *mo_shell)
{
	t_block	*nav;

	nav = mo_shell->splitted_input;
	if (!nav)
		return ;
	while (nav)
		nav = nav->next;
	//TODO Setup pipes and redirections from right to left, redirections steal the pipe
	while (nav)
	{
		nav = nav->prev;
	}

	nav = mo_shell->splitted_input;
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
