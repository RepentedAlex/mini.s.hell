/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_not_dirfile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:35:43 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/23 15:35:45 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "minishell.h"

bool	check_if_dirfile_exist(char *path)
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
		return (true);
	}
	fd = open(path, O_RDONLY);
	if (fd > -1)
	{
		printf("%s: Permission denied\n", path);
		close(fd);
		return (true);
	}
	printf("%s: No such file or directory\n", path);
	return (false);
}

bool	check_not_dirfile(t_block **head)
{
	t_block	*nav;

	nav = *head;
	if (!nav)
		return (0);
	if (ft_strchr(nav->str, '/'))
	{
		check_if_dirfile_exist(nav->str);
		return (true);
	}
	nav = nav->next;
	while (nav)
	{
		if (nav->prev->type != RAW)
		{
			if (ft_strchr(nav->str, '/'))
			{
				check_if_dirfile_exist(nav->str);
				return (true);
			}
		}
		nav = nav->next;
	}
	return (false);
}
