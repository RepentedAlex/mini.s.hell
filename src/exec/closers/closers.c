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

t_error	wait_for_processes(t_pids *pids_array)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = 0;
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
