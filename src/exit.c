/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:37:25 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/08 18:37:28 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_block **head)
{
	t_block	*nav;
	t_block	*tmp;

	nav = *head;
	while (nav)
	{
		if (nav->str)
		{
			free(nav->str);
			nav->str = NULL;
		}
		tmp = nav->next;
		free(nav);
		nav = tmp;
	}
	*head = NULL;
}

void	free_2d_tab(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_cmd_table(t_cmd **head)
{
	t_cmd	*nav;
	t_cmd	*tmp;

	nav = *head;
	while (nav)
	{
		if (nav->cmd != NULL)
		{
			free(nav->cmd);
			nav->cmd = NULL;
		}
		if (nav->args)
		{
			free_2d_tab(nav->args);
			nav->args = NULL;
		}
		tmp = nav->next;
		free(nav);
		nav = tmp;
	}
	*head = NULL;
}

void	garbage_collect(t_mo_shell *data, int mode)
{
	if (data->splitted_input)
		free_list(&data->splitted_input);
	if (data->og_input)
		(free(data->og_input), data->og_input = NULL);
	if (data->clean_input)
		(free(data->clean_input), data->clean_input = NULL);
	if (data->expanded_input)
		(free(data->expanded_input), data->expanded_input = NULL);
	if (data->cmds_table)
		(free_cmd_table(&data->cmds_table), data->cmds_table = NULL);
	if (mode == 1)
	{
		rl_clear_history();
		if (data->shell_env)
			(free_2d_tab(data->shell_env), data->shell_env = NULL);
	}
}
