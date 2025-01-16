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

int	check_if_dirfile_exist(char *path, t_mo_shell *mo_shell)
{
	DIR	*dir;
	int	fd;

	fd = 0;
	dir = 0;
	if (path[0] == '\0')
		return (0);
	dir = opendir(path);
	if (dir != NULL)
	{
		(closedir(dir), printf("%s: Is a directory\n", path));
		return (mo_shell->last_exit_status = 126, 1);
	}
	if (access(path, R_OK | X_OK) == -1)
	{
		printf("%s: Permission denied\n", path);
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		return (-1);
	}
	close(fd);
	return (0);
}

t_error	init_check_nd(t_block **nav, int *cide_ret, t_block **head)
{
	*cide_ret = 0;
	*nav = *head;
	if (!*nav)
		return (ERROR);
	return (NO_ERROR);
}

int	check_not_dirfile(t_block **head, t_mo_shell *mo_shell)
{
	t_block	*nav;
	int		cide_ret;

	if (init_check_nd(&nav, &cide_ret, head) == ERROR)
		return (0);
	if (!nav->prev || nav->prev->type == PIPE)
	{
		if (ft_strchr(nav->str, '/'))
		{
			cide_ret = check_if_dirfile_exist(nav->str, mo_shell);
			if (cide_ret == -1)
				return (-1);
			if (cide_ret == 1)
				return (mo_shell->last_exit_status = 126, 1);
		}
		nav = nav->next;
		while (nav)
		{
			if (nav->prev->type != RAW && ft_strchr(nav->str, '/') && \
				check_if_dirfile_exist(nav->str, mo_shell) == true)
				return (1);
			nav = nav->next;
		}
	}
	return (0);
}
