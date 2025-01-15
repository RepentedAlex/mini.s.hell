/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:22:17 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 14:22:20 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"

t_cmd	*init_exec_seq(t_mo_shell *mo_shell, t_pipes *pipes, t_pids *pids)
{
	t_cmd		*to_launch;

	to_launch = mo_shell->cmds_table;
	ft_memset(pids->pid, 0, sizeof(pids->pid));
	ft_memset(pipes->pipe, -1, sizeof(pipes->pipe));
	pipes->pipe_i = -1;
	pids->pid_i = -1;
	to_launch->cp_i = dup(STDIN_FILENO);
	to_launch->cp_o = dup(STDOUT_FILENO);
	return (to_launch);
}
