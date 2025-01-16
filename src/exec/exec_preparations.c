/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_preparations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:50:10 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/04 18:09:32 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/// @brief Handles the setup of the pipes and redirections. Handles heredoc
/// as well.
/// @param mo_shell Pointer to the Mother Shell structure.
/// @return ERROR on error, NO_ERROR otherwise.
t_error	pipeline_setup(t_mo_shell *mo_shell)
{
	mo_shell->cmds_table = spltd_in_to_cmd_blocks(&mo_shell->splitted_input);
	if (mo_shell->cmds_table == NULL)
		return (ERROR);
	if (fill_cmd_and_args(mo_shell) == ERROR)
		return (ERROR);
	if (open_redir_files(&mo_shell->cmds_table, &mo_shell->splitted_input, \
		mo_shell) == ERROR)
		return (ERROR);
	if (expand_cmd_path(&mo_shell->cmds_table, mo_shell->shell_env) == ERROR)
		return (mo_shell->last_exit_status = 127, ERROR);
	return (NO_ERROR);
}

t_cmd	*spltd_in_to_cmd_blocks(t_block **head)
{
	t_block	*nav;
	t_cmd	*tmp;
	int		number_of_cmds;
	t_cmd	*ret;

	nav = init_spl_to_cmdb(&ret, &tmp, &number_of_cmds, head);
	while (nav)
	{
		if (nav->type == PIPE)
			number_of_cmds++;
		nav = nav->next;
	}
	ret = cmd_new(NULL);
	if (!ret)
		return (NULL);
	number_of_cmds--;
	while (number_of_cmds > 0)
	{
		tmp = cmd_new(NULL);
		if (!tmp)
			return (NULL);
		cmd_add_back(ret, tmp);
		number_of_cmds--;
	}
	return (ret);
}

t_error	discriminate_out_type(t_block *nav_block, t_cmd *nav_cmd)
{
	if (nav_block->prev->type == APPEND)
	{
		if (open_file_out(nav_block, nav_cmd, 2) == ERROR)
			return (ERROR);
	}
	else if (open_file_out(nav_block, nav_cmd, 1) == ERROR)
		return (ERROR);
	return (NO_ERROR);
}

/// @brief Opens files for the command blocks, handles several redirections.
/// @param cmd_head The command table list's head.
/// @param block_head The block list's head.
/// @return ERROR if file couldn't be opened, NO_ERROR otherwise.
t_error	open_redir_files(t_cmd **cmd_head, t_block **block_head, t_mo_shell \
	*mo_shell)
{
	t_block	*nav_block;
	t_cmd	*nav_cmd;

	nav_block = *block_head;
	nav_cmd = *cmd_head;
	while (nav_block)
	{
		if (nav_block->type == INFILE && open_file_in(nav_block, nav_cmd, \
			1, mo_shell) == ERROR)
			return (ft_putstr_fd("No such file or directory\n", \
				STDERR_FILENO), ERROR);
		if (nav_block->type == OUTFILE && discriminate_out_type(nav_block, \
			nav_cmd) == ERROR)
			return (ERROR);
		if (nav_block->type == EOFHD && open_file_in(nav_block, nav_cmd, \
			2, mo_shell) == ERROR)
			return (ft_putstr_fd("No such file or directory\n", \
				STDERR_FILENO), ERROR);
		nav_block = nav_block->next;
	}
	return (NO_ERROR);
}
