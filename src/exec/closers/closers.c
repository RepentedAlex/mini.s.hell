/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:26:08 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 14:26:11 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_pipes *pipes)
{
	if (pipes->pipe_i >= 0)
	{
		if (pipes->pipe[pipes->pipe_i][0] != -1)
			close(pipes->pipe[pipes->pipe_i][0]);
		if (pipes->pipe[pipes->pipe_i][1] != -1)
			close(pipes->pipe[pipes->pipe_i][1]);
	}
}

int	wait_for_processes(t_pids *pids_array, t_mo_shell *mo_shell)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = mo_shell->les;
	i = 0;
	while (i <= pids_array->pid_i)
	{
		if (pids_array->pid[i])
		{
			if (waitpid(pids_array->pid[i], &status, 0) == -1)
				(perror("waitpid"), exit(EXIT_FAILURE));
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
		i++;
	}
	return (exit_status);
}
