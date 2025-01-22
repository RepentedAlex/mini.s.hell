/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:03:09 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 14:03:12 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

void	handler_dup2(t_cmd *to_launch, t_pipes *pipes)
{
	if (to_launch->fd_i != STDIN_FILENO)
		(dup2(to_launch->fd_i, STDIN_FILENO), close(to_launch->fd_i));
	else if (to_launch->prev)
	{
		dup2(pipes->pipe[pipes->pipe_i - 1][0], STDIN_FILENO);
		close(pipes->pipe[pipes->pipe_i - 1][0]);
	}
	if (to_launch->fd_o != STDOUT_FILENO)
		(dup2(to_launch->fd_o, STDOUT_FILENO), close(to_launch->fd_o));
	else if (to_launch->next)
	{
		dup2(pipes->pipe[pipes->pipe_i][1], STDOUT_FILENO);
		close(pipes->pipe[pipes->pipe_i][1]);
	}
	if (to_launch->prev)
		close(pipes->pipe[pipes->pipe_i - 1][1]);
	if (to_launch->next)
		close(pipes->pipe[pipes->pipe_i][0]);
}

/// @brief
/// @param to_launch The current command we want to execute.
/// @param pipes The current pipe.
/// @param envp The environment variables
/// @param mo_shell
int	child_process_ext(t_cmd *to_launch, t_pipes *pipes, char *envp[], \
	t_mo_shell *mo_shell)
{
	if (check_if_dirfile_exist(to_launch->cmd, mo_shell))
		exit(126);
	handler_dup2(to_launch, pipes);
	execve(to_launch->cmd, to_launch->args, envp);
	err_msg(CMD_NOT_FOUND_MSG, to_launch->cmd);
	exit(127);
}

int	child_process_bi(t_cmd *to_launch, t_pipes *pipes, t_mo_shell *mo_shell, \
	int mode)
{
	int	(*f_builtin)(char **, t_mo_shell *mo_shell, t_cmd *cmd);

	if (mode == 1 && ft_strcmp(to_launch->cmd, "exit") == 0)
		mode = 0;
	if (mode == 0)
	{
		handler_dup2(to_launch, pipes);
		f_builtin = (launch_builtin(to_launch));
		if (f_builtin(to_launch->args, mo_shell, to_launch) == 0)
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	if (mode == 1)
	{
		handler_dup2(to_launch, pipes);
		f_builtin = (launch_builtin(to_launch));
		mo_shell->last_exit_status = f_builtin(to_launch->args, mo_shell, \
			to_launch);
		if (mo_shell->last_exit_status == 0)
			return (EXIT_SUCCESS);
		return (mo_shell->last_exit_status);
	}
	return (EXIT_FAILURE);
}

/// @brief Runs a command that is not builtin into the shell.
/// @param mo_shell The Mother Shell structure.
/// @param to_launch The command that is next in line to be run.
/// @param pipes_array The srtucture that holds all the pipes file descriptors.
/// @param pids_array The structure that holds all the PIDs.
int	fork_for_cmd(t_mo_shell *mo_shell, t_cmd *to_launch, \
	t_pipes *pipes_array, t_pids *pids_array)
{
	int		ret;

	ret = mo_shell->last_exit_status;
	if (is_builtin(to_launch->cmd) == true && !to_launch->prev && \
		!to_launch->next)
	{
		ret = child_process_bi(to_launch, pipes_array, mo_shell, 1);
	}
	else
	{
		pids_array->pid[pids_array->pid_i] = fork();
		if (pids_array->pid[pids_array->pid_i] == -1)
			(perror("fork error\n"), exit(EXIT_FAILURE));
		if (pids_array->pid[pids_array->pid_i] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			if (is_builtin(to_launch->cmd) == false)
				child_process_ext(to_launch, pipes_array, mo_shell->shell_env, \
					mo_shell);
			if (is_builtin(to_launch->cmd) == true)
				child_process_bi(to_launch, pipes_array, mo_shell, 0);
		}
	}
	return (ret);
}
