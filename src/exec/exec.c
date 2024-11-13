/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:39:02 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/05 15:51:32 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"

char	**for_first_arg(char *str)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 2);
	if (!ret)
	{
		return (NULL);
	}
	ret[0] = ft_strdup(str);
	ret[1] = NULL;
	return (ret);
}

char	**add_str_to_array(char **array, char *str)
{
	char	**nav;
	char	**ret;
	int		i;

	ret = NULL;
	nav = array;
	if (!nav)
		return (for_first_arg(str));
	i = 0;
	while (nav[i] != NULL)
		i++;
	ret = (char **) malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (NULL);
	i = -1;
	while (array[++i] != NULL)
		ret[i] = ft_strdup(array[i]);
	ret[i] = ft_strdup(str);
	ret[i + 1] = NULL;
	(free_2d_tab(array), array = NULL);
	return (ret);
}

void	handler_dup2(t_cmd *to_launch, t_pipes *pipes)
{
	if (to_launch->fd_i != STDIN_FILENO)
		dup2(to_launch->fd_i, STDIN_FILENO);
	else if (to_launch->prev)
		dup2(pipes->pipe[pipes->pipe_i - 1][0], STDIN_FILENO);
	if (to_launch->fd_o != STDOUT_FILENO)
		dup2(to_launch->fd_o, STDOUT_FILENO);
	else if (to_launch->next)
		dup2(pipes->pipe[pipes->pipe_i][1], STDOUT_FILENO);
	if (to_launch->prev)
	{
		close(pipes->pipe[pipes->pipe_i - 1][0]);	//Close read end of previous pipe
		close(pipes->pipe[pipes->pipe_i - 1][1]);	//Close write end of previous pipe
	}
	if (to_launch->next)
	{
		close(pipes->pipe[pipes->pipe_i][0]);	//Close read end of previous pipe
		close(pipes->pipe[pipes->pipe_i][1]);	//Close write end of previous pipe
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
	perror("execve");
//	 exit(EXIT_FAILURE);
	return (1);
}

int child_process_bi(t_cmd *to_launch, t_pipes *pipes, t_mo_shell *mo_shell, int mode)
{
	int	(*f_builtin)(char **, t_mo_shell *mo_shell, t_cmd *cmd);

	if (mode == 0)
	{
		handler_dup2(to_launch, pipes);
		f_builtin = (g_launch_builtins(to_launch));
		if (f_builtin(to_launch->args, mo_shell, to_launch) == 0)
			exit(EXIT_SUCCESS);
		perror("mini.s.hell");
		exit(EXIT_FAILURE);
	}
	if (mode == 1)
	{
		handler_dup2(to_launch, pipes);
		f_builtin = (g_launch_builtins(to_launch));
		if (f_builtin(to_launch->args, mo_shell, to_launch) == 0)
			return (EXIT_SUCCESS);
		perror("mini.s.hell");
		return (mo_shell->last_exit_status);
		// return (EXIT_FAILURE);
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
	//TODO Fill heredoc for command here

//	if (is_builtin(to_launch->cmd) == true && !to_launch->prev && !to_launch->next)
//	{
//		child_process_bi(to_launch, pipes_array, mo_shell, 1);
//	}
//	else
//	{
		pids_array->pid[pids_array->pid_i] = fork();
		if (pids_array->pid[pids_array->pid_i] == -1)
			(perror("fork error\n"), exit(EXIT_FAILURE));
//	}
	if (pids_array->pid[pids_array->pid_i] == 0)
	{
		if (is_builtin(to_launch->cmd) == false)
			child_process_ext(to_launch, pipes_array, mo_shell->shell_env);
		if (is_builtin(to_launch->cmd) == true)
			child_process_bi(to_launch, pipes_array, mo_shell, 0);
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
	int		exit_status;

	to_launch = mo_shell->cmds_table;
	ft_memset(pids_array.pid, 0, sizeof(pids_array.pid));
	ft_memset(pipes_array.pipe, -1, sizeof(pipes_array.pipe));
	pipes_array.pipe_i = -1;
	pids_array.pid_i = -1;
	while (to_launch)
	{
		pipes_array.pipe_i++;
		pids_array.pid_i++;
		if (to_launch->next && pipe(pipes_array.pipe[pipes_array.pipe_i]) == -1)
		{
			perror("pipe error");
			exit(EXIT_FAILURE);
		}
		fork_for_cmd(mo_shell, to_launch, &pipes_array, &pids_array);
		to_launch = to_launch->next;
	}
	while (pipes_array.pipe_i > 0)
	{
		close(pipes_array.pipe[pipes_array.pipe_i - 1][0]);
		close(pipes_array.pipe[pipes_array.pipe_i - 1][1]);
		pipes_array.pipe_i--;
	}
	//Wait for all children to finish their task
	i = -1;
	while (++i <= pids_array.pid_i)
		if (pids_array.pid[i] != 0)
			waitpid(pids_array.pid[i], &exit_status, WIFEXITED(exit_status));
//	if (WIFEXITED(exit_status))
//		mo_shell->last_exit_status = WIFEXITED(exit_status);
		// printf("Exit status: %d\n", WEXITSTATUS(exit_status));
	return (exit_status);
}

/// @brief This function handles all things related to the execution.
/// @param mo_shell The pointer to the mother shell structure.
/// @return ERROR on error, NO_ERROR otherwise.
t_error	execution(t_mo_shell *mo_shell)
{
	if (!mo_shell->splitted_input)
		return (ERROR);
	pipeline_setup(mo_shell);
	execution_sequence(mo_shell);
	close_fds(&mo_shell->cmds_table);
	return (NO_ERROR);
}
