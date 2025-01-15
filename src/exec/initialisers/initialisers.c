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

void	init_cmd_args_fill(t_mo_shell *mo_shell, t_block **nav_block, \
	t_cmd **nav_cmd, bool *block_has_cmd)
{
	*nav_cmd = mo_shell->cmds_table;
	*nav_block = mo_shell->splitted_input;
	*block_has_cmd = false;
}

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

t_block	*init_spl_to_cmdb(t_cmd **ret, t_cmd **tmp, int *number_of_cmds, \
	t_block **head)
{
	t_block	*nav;

	*ret = NULL;
	*tmp = NULL;
	*number_of_cmds = 1;
	nav = *head;
	return (nav);
}
