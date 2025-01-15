/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:03:17 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 17:03:25 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

t_error	fill_cmd(t_block *nav_block, t_cmd *nav_cmd, bool *block_has_cmd)
{
	*block_has_cmd = true;
	if (nav_cmd->cmd)
		free(nav_cmd->cmd);
	nav_cmd->cmd = ft_strdup(nav_block->str);
	add_str_to_ra(&nav_cmd->args, nav_block->str);
	if (!nav_cmd->args)
		return (ERROR);
	nav_block->type = CMD;
	return (NO_ERROR);
}

/// @brief Fills the cmd and args fields of each t_cmd node.
/// @param mo_shell The block list's head.
t_error	fill_cmd_and_args(t_mo_shell *mo_shell)
{
	t_block	*nav_block;
	t_cmd	*nav_cmd;
	bool	blk_hs_cmd;

	init_cmd_args_fill(mo_shell, &nav_block, &nav_cmd, &blk_hs_cmd);
	while (nav_cmd && nav_block)
	{
		if (!blk_hs_cmd && nav_block->type == RAW)
		{
			if (fill_cmd(nav_block, nav_cmd, &blk_hs_cmd) == ERROR)
				return (ERROR);
		}
		else if (blk_hs_cmd && nav_block->type == RAW)
		{
			if (add_str_to_ra(&nav_cmd->args, nav_block->str) && !nav_cmd->args)
				return (ERROR);
		}
		if (nav_block->type == PIPE)
		{
			nav_cmd = nav_cmd->next;
			blk_hs_cmd = false;
		}
		nav_block = nav_block->next;
	}
	return (NO_ERROR);
}
