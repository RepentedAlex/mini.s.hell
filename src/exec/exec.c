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
	ret = (char **)malloc(sizeof(char *) * (i + 2));
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

/// @brief Runs the commands, iterating through the commands table.
/// @param mo_shell The pointer to the mother shell structure.
void	execute_cl(t_mo_shell *mo_shell)
{
	t_cmd	*to_launch;

	to_launch = mo_shell->cmds_table;
	while (to_launch)
	{
		if (is_builtin(to_launch->cmd) == true)
		{
			//exec builtin
			launch_builtins(to_launch);
		}
		else
		{
			//execve
		}
		to_launch = to_launch->next;
	}
	close_fds(&mo_shell->cmds_table);
}

/// @brief
/// @param to_launch The current command we want to execute.
/// @param pipes The current pipe.
/// @param envp The environment variables
void	child_process(t_cmd *to_launch, t_pipes *pipes, char *envp[])
{
	//IF fd_in not standard
	if (to_launch->fd_i != STDIN_FILENO)
	{
		//dup2 from STDIN to fd from fd_in
		// printf("%s: redirecting stdin to infile\n", to_launch->cmd);
		dup2(to_launch->fd_i, STDIN_FILENO);
	}
	//ELSE IF not first command
	else if (to_launch->prev)
	{
		//Read from previous pipe's reading end
		// printf("%s: redirecting stdin to previous pipe reading end\n", to_launch->cmd);
		dup2(pipes->pipe[pipes->pipe_i - 1][0], STDIN_FILENO);
	}
	//IF fd_out not standard
	if (to_launch->fd_o !=  STDOUT_FILENO)
	{
		//dup2 from STDOUT to fd from fd_out
		// printf("%s: redirecting stdout to outfile\n", to_launch->cmd);
		dup2(to_launch->fd_o, STDOUT_FILENO);
	}
	//ELSE IF not last command
	else if (to_launch->next)
	{
		//Write to next pipe's writing end
		// printf("%s: redirecting stdout to next pipe writing end\n", to_launch->cmd);
		dup2(pipes->pipe[pipes->pipe_i][1], STDOUT_FILENO);
	}

	//Might need to redirect output to next pipe

	//IF not first command
	if (to_launch->prev)
	{
		//CLOSE previous pipe
		// close(pipes->pipe[pipes->pipe_i - 1][0]);
		// close(pipes->pipe[pipes->pipe_i - 1][1]);
	}
	//CLOSE current pipe
	if (to_launch->next && to_launch->fd_o != STDOUT_FILENO)
		close(pipes->pipe[pipes->pipe_i][0]);
	if (to_launch->next && to_launch->fd_i != STDIN_FILENO)
		close(pipes->pipe[pipes->pipe_i][1]);

	//Execute command
	execve(to_launch->cmd, to_launch->args, envp);
	printf("execve error\n");
	exit(EXIT_FAILURE);
}

/// @brief
/// @param mo_shell
void	execution_sequence(t_mo_shell *mo_shell)
{
	t_cmd	*to_launch;
	t_pipes	pipes_array;
	t_pids	pids_array;

	to_launch = mo_shell->cmds_table;
	pipes_array.pipe_i = -1;
	pids_array.pid_i = -1;
	while (to_launch)
	{
		pipes_array.pipe_i++;
		pids_array.pid_i++;

		//IF there's a command next, create pipe
		if (to_launch->next && pipe(pipes_array.pipe[pipes_array.pipe_i]) == -1)
		{
			printf("pipe error\n");
			exit(EXIT_FAILURE);
		}

		//IF is a builtin
		if (is_builtin(to_launch->cmd) == true)
		{
			//Execute the command without fork
		}

		//IF is not a builtin, fork
		else
		{
			if ((pids_array.pid[pids_array.pid_i] = fork()) == -1)
			{
				printf("fork error\n");
				exit(EXIT_FAILURE); ;
			}
			if (pids_array.pid[pids_array.pid_i] == 0)
				child_process(to_launch, &pipes_array, mo_shell->shell_env);
			else
				parent_process();
		}
		//Go to next command
		to_launch = to_launch->next;
	}
	//Wait for all pids to finish (might only be needed if execution is in foreground
	waitpid(0, NULL, WUNTRACED);
}

/// @brief This function handles all things related to the execution.
/// @param mo_shell The pointer to the mother shell structure.
/// @return ERROR on error, NO_ERROR otherwise.
t_error	execution(t_mo_shell *mo_shell)
{
	if (!mo_shell->splitted_input)
		return (ERROR);
	pipeline_setup(mo_shell);
	//TODO Exec
	execution_sequence(mo_shell);
	close_fds(&mo_shell->cmds_table);
	return (NO_ERROR);
}
