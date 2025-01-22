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

/// @brief Add a string to an array
/// @param array
/// @param str
/// @return
t_error	add_str_to_ra(char ***array, char *str)
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

void	run_cmd(t_mo_shell *mo_shell, t_cmd *to_launch, t_pipes *pipes, \
	t_pids *pids)
{
	while (to_launch)
	{
		pipes->pipe_i++;
		pids->pid_i++;
		if (to_launch->next)
			if (pipe(pipes->pipe[pipes->pipe_i]) == -1)
				(perror("pipe error"), exit(EXIT_FAILURE));
		mo_shell->last_exit_status = fork_for_cmd(mo_shell, to_launch, \
			pipes, pids);
		if (to_launch->prev)
		{
			if (pipes->pipe[pipes->pipe_i - 1][0] != -1)
				close(pipes->pipe[pipes->pipe_i - 1][0]);
			if (pipes->pipe[pipes->pipe_i - 1][1] != -1)
				close(pipes->pipe[pipes->pipe_i - 1][1]);
		}
		to_launch = to_launch->next;
	}
	close_pipes(pipes);
}

/// @brief Handles the execution of the commands, from left to right.
/// @param mo_shell The Mother_Shell structure.
int	execution_sequence(t_mo_shell *mo_shell)
{
	t_cmd	*to_launch;
	t_pipes	pipes_array;
	t_pids	pids_array;
	int		ret;

	to_launch = init_exec_seq(mo_shell, &pipes_array, &pids_array);
	run_cmd(mo_shell, to_launch, &pipes_array, &pids_array);
	ret = wait_for_processes(&pids_array, mo_shell);
	return (ret);
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
