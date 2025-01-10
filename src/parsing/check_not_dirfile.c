/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_not_dirfile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:35:43 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/29 18:10:21 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "minishell.h"

int check_if_dirfile_exist(char *path, t_mo_shell *mo_shell)
{
	DIR	*dir;
	int	fd;

	fd = 0;
	dir = 0;
	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		printf("%s: Is a directory\n", path);
		mo_shell->last_exit_status = 126;
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd > -1)
	{
		if (access(path, R_OK | X_OK) == -1)
		{
			printf("%s: Permission denied\n", path);
		}
		close(fd);
		return (1);
	}
	// printf("%s: No such file or directory\n", path);
	return (0);
}

int check_not_dirfile(t_block **head, t_mo_shell *mo_shell)
{
	t_block	*nav;

	nav = *head;
	if (!nav)
		return (0);
	if (ft_strchr(nav->str, '/'))
	{
		if (check_if_dirfile_exist(nav->str, mo_shell) == -1)
			return (-1);
	}
	nav = nav->next;
	while (nav)
	{
		if (nav->prev->type != RAW)
		{
			if (ft_strchr(nav->str, '/'))
			{
				if (check_if_dirfile_exist(nav->str, mo_shell) == true)
					return (1);
			}
		}
		nav = nav->next;
	}
	return (0);
}
