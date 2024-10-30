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

void	execution_sequence(t_mo_shell *mo_shell)
{
	t_cmd	*to_launch;
	int		pipe_fd[1024][2];
	int		pipe_i;
	int		pid[1024];
	int		pid_i;

	to_launch = mo_shell->cmds_table;
	pipe_i = -1;
	pid_i = -1;
	while (to_launch)
	{
		pid_i++;
		pipe_i++;
		if (is_builtin(to_launch->cmd))
		{
			launch_builtins(to_launch);
		}
		else
		{
			if (to_launch->next) //Si on a une commande ensuite alors on cree un pipe
			{
				if (pipe(pipe_fd[pipe_i]) == -1)
				{
					printf("pipe error\n");
					exit(EXIT_FAILURE); ;
				}
			}

			if ((pid[pid_i] = fork()) == -1)
			{
				printf("fork error\n");
				exit(EXIT_FAILURE); ;
			}
			if (pid[pid_i] == 0) //PIPES
			{
				if (pipe_i > 0) //SI PIPE AVANT
				{
					dup2(pipe_fd[pipe_i - 1][0], STDIN_FILENO);
				}
				if (to_launch->next)
				{
					dup2(pipe_fd[pipe_i][1], STDOUT_FILENO);
				}
				if (pipe_i > 0)
				{
					close(pipe_fd[pipe_i - 1][0]);
					close(pipe_fd[pipe_i - 1][1]);
				}
				if (to_launch->next)
				{
					close(pipe_fd[pipe_i][0]);
					close(pipe_fd[pipe_i][1]);
				}

				execve(to_launch->cmd, to_launch->args, mo_shell->shell_env);
				printf("execve error\n");
				exit(EXIT_FAILURE); ;
			}
		}
		to_launch = to_launch->next;
	}
		waitpid(pid[0], NULL, 0);
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
