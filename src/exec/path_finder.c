/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:17:55 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/03 17:30:51 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"

void	ft_free_tab(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	*get_env(char *envp[])
{
	int		i;
	int		j;
	char	*env_string;

	i = 0;
	while (envp && envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		env_string = ft_substr(envp[i], 0, j);
		if (ft_strncmp(env_string, "PATH", j) == 0)
		{
			free(env_string);
			return (envp[i] + j + 1);
		}
		free(env_string);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char *envp[])
{
	int		i;
	char	*exec;
	char	**all_paths;
	char	*part_path;
	char	**cmds_array;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	i = 0;
	all_paths = ft_split(get_env(envp), ':');
	cmds_array = malloc(sizeof(char *) * 2);
	if (!cmds_array)
		return (NULL);
	*cmds_array = ft_strdup(cmd);
	cmds_array[1] = NULL;
	while (all_paths && all_paths[i])
	{
		part_path = ft_strjoin(all_paths[i], "/");
		exec = ft_strjoin(part_path, cmds_array[0]);
		(free(part_path), part_path = NULL);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_free_tab(cmds_array), ft_free_tab(all_paths), exec);
		(free(exec), i++);
	}
	return (ft_free_tab(cmds_array), ft_free_tab(all_paths), NULL);
}
