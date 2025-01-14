/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:39:02 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/07 11:29:56 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"

t_error	for_first_arg(char *str, char ***env)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 2);
	if (!ret)
	{
		return (ERROR);
	}
	ret[0] = ft_strdup(str);
	ret[1] = NULL;
	*env = ret;
	return (NO_ERROR);
}

t_error	add_str_to_array(char ***array, char *str)
{
	char	**nav;
	char	**ret;
	int		i;

	ret = NULL;
	nav = *array;
	if (!nav || nav[0] == NULL)
		return (for_first_arg(str, array), NO_ERROR);
	i = 0;
	while (nav[i] != NULL)
		i++;
	ret = (char **) malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (NULL);
	i = -1;
	while ((*array)[++i] != NULL)
		ret[i] = ft_strdup((*array)[i]);
	ret[i] = ft_strdup(str);
	ret[i + 1] = NULL;
	(free_2d_tab(*array), *array = NULL);
	*array = ret;
	return (NO_ERROR);
}

void	handler_dup2(t_cmd *to_launch, t_pipes *pipes)
{
	if (to_launch->fd_i != STDIN_FILENO)
	{
		dup2(to_launch->fd_i, STDIN_FILENO);
		close(to_launch->fd_i);
	}
	else if (to_launch->prev)
	{
		dup2(pipes->pipe[pipes->pipe_i - 1][0], STDIN_FILENO);
		close(pipes->pipe[pipes->pipe_i - 1][0]);
	}
	if (to_launch->fd_o != STDOUT_FILENO)
	{
		dup2(to_launch->fd_o, STDOUT_FILENO);
		close(to_launch->fd_o);
	}
	else if (to_launch->next)
	{
		dup2(pipes->pipe[pipes->pipe_i][1], STDOUT_FILENO);
		close(pipes->pipe[pipes->pipe_i][1]);
	}
	if (to_launch->prev)
	{
		close(pipes->pipe[pipes->pipe_i - 1][1]);
	}
	if (to_launch->next)
	{
		close(pipes->pipe[pipes->pipe_i][0]);
	}
}

/// @brief
/// @param to_launch The current command we want to execute.
/// @param pipes The current pipe.
/// @param envp The environment variables
int child_process_ext(t_cmd *to_launch, t_pipes *pipes, char *envp[])
{
	handler_dup2(to_launch, pipes);
	execve(to_launch->cmd, to_launch->args, envp);
	ft_putstr_fd("mini.s.hell: ", 2);
	ft_putstr_fd(to_launch->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

int child_process_bi(t_cmd *to_launch, t_pipes *pipes, t_mo_shell *mo_shell, int mode)
{
	int	(*f_builtin)(char **, t_mo_shell *mo_shell, t_cmd *cmd);
	if (mode == 1 && ft_strcmp(to_launch->cmd, "exit") == 0)
		mode = 0;
	if (mode == 0)
	{
		handler_dup2(to_launch, pipes);
		f_builtin = (g_launch_builtins(to_launch));
		if (f_builtin(to_launch->args, mo_shell, to_launch) == 0)
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	if (mode == 1)
	{
		handler_dup2(to_launch, pipes);
		f_builtin = (g_launch_builtins(to_launch));
		mo_shell->last_exit_status = f_builtin(to_launch->args, mo_shell, to_launch);
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
	if (is_builtin(to_launch->cmd) == true && !to_launch->prev && !to_launch->next)
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
				child_process_ext(to_launch, pipes_array, mo_shell->shell_env);
			if (is_builtin(to_launch->cmd) == true)
				child_process_bi(to_launch, pipes_array, mo_shell, 0);
		}
	}
	return (ret);
}

/// @brief Handles the execution of the commands, from left to right.
/// @param mo_shell The Mother_Shell structure.
int	execution_sequence(t_mo_shell *mo_shell)
{
	t_cmd	*to_launch;
	t_pipes	pipes_array;
	t_pids	pids_array;
	int		i;
	int		status;
	int		exit_status;

	to_launch = mo_shell->cmds_table;
	ft_memset(pids_array.pid, 0, sizeof(pids_array.pid));
	ft_memset(pipes_array.pipe, -1, sizeof(pipes_array.pipe));
	exit_status = mo_shell->last_exit_status;
	pipes_array.pipe_i = -1;
	pids_array.pid_i = -1;
	to_launch->cp_i = dup(STDIN_FILENO);
	to_launch->cp_o = dup(STDOUT_FILENO);
	while (to_launch)
	{
		pipes_array.pipe_i++;
		pids_array.pid_i++;
		if (!to_launch->cmd)
		{
			to_launch = to_launch->next;
			continue ;
		}
		if (to_launch->next)
			if (pipe(pipes_array.pipe[pipes_array.pipe_i]) == -1) //If pipe() fails
				(perror("pipe error"), exit(EXIT_FAILURE));
		exit_status = fork_for_cmd(mo_shell, to_launch, &pipes_array, &pids_array);
		if (to_launch->prev)
		{
			if (pipes_array.pipe[pipes_array.pipe_i - 1][0] != -1)
				close(pipes_array.pipe[pipes_array.pipe_i - 1][0]);
			if (pipes_array.pipe[pipes_array.pipe_i - 1][1] != -1)
				close(pipes_array.pipe[pipes_array.pipe_i - 1][1]);
		}
		to_launch = to_launch->next;
	}
	if (pipes_array.pipe_i >= 0)
	{
		if (pipes_array.pipe[pipes_array.pipe_i][0] != -1)
			close(pipes_array.pipe[pipes_array.pipe_i][0]);
		if (pipes_array.pipe[pipes_array.pipe_i][1] != -1)
			close(pipes_array.pipe[pipes_array.pipe_i][1]);
	}
	i = 0;
	while (i <= pids_array.pid_i)
	{
		if (pids_array.pid[i])
		{
			if (waitpid(pids_array.pid[i], &status, 0) == -1)
				(perror("waitpid"), exit(EXIT_FAILURE));
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
		i++;
	}
	mo_shell->last_exit_status = exit_status;
	return (mo_shell->last_exit_status);
}

/// @brief This function handles all things related to the execution.
/// @param mo_shell The pointer to the mother shell structure.
/// @return ERROR on error, NO_ERROR otherwise.
t_error	execution(t_mo_shell *mo_shell)
{
	if (!mo_shell->splitted_input)
		return (ERROR);
	if (pipeline_setup(mo_shell) == ERROR)
		return (close_fds(&mo_shell->cmds_table), ERROR);
	mo_shell->last_exit_status = execution_sequence(mo_shell);
	close_fds(&mo_shell->cmds_table);
	return (NO_ERROR);
}
