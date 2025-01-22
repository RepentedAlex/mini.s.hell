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

int	check_if_dirfile_exist(char *path)
{
	DIR	*dir;
	int	fd;

	fd = 0;
	dir = 0;
	if (path[0] == '\0')
		return (0);
	dir = opendir(path);
	if (dir != NULL)
		return (closedir(dir), err_msg(IS_DIR_MSG, path), IS_DIR_CODE);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		if (access(path, F_OK) == -1)
			return (err_msg(NO_SCH_FOD_MSG, path), NO_SCH_FOD_CODE);
		return (err_msg(PERM_DENIED_MSG, path), PERM_DENIED_CODE);
	}
	close(fd);
	if (access(path, R_OK | X_OK) == -1)
		return (err_msg(PERM_DENIED_MSG, path), PERM_DENIED_CODE);
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
			cide_ret = check_if_dirfile_exist(nav->str);
			if (cide_ret == -1)
				return (-1);
			if (cide_ret == 1)
				return (mo_shell->les = 126, 1);
		}
		nav = nav->next;
		while (nav)
		{
			if (nav->prev->type != RAW && ft_strchr(nav->str, '/') && \
				check_if_dirfile_exist(nav->str) == true)
				return (1);
			nav = nav->next;
		}
	}
	return (0);
}
