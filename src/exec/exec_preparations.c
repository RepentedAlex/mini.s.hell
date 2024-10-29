/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_preparations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:50:10 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/29 15:50:12 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/// @brief Fills the cmd and args fields of each t_cmd node.
/// @param cmd_head The command table list's head.
/// @param block_head The block list's head.
void	fill_cmd_and_args(t_cmd **cmd_head, t_block **block_head)
{
	t_block	*nav_block;
	t_cmd	*nav_cmd;
	bool	block_has_cmd;

	nav_cmd = *cmd_head;
	nav_block = *block_head;
	while (nav_cmd)
	{
		block_has_cmd = false;
		while (nav_block)
		{
			if (nav_block->type == PIPE)
			{
				nav_block = nav_block->next;
				break ;
			}
			if (!block_has_cmd && nav_block->type == RAW)
			{
				block_has_cmd = true;
				nav_cmd->cmd = ft_strdup(nav_block->str);
				nav_block->type = CMD;
			}
			else if (block_has_cmd && nav_block->type == RAW)
				nav_cmd->args = add_str_to_array(nav_cmd->args, nav_block->str);
			nav_block = nav_block->next;
		}
		nav_cmd = nav_cmd->next;
	}
}

/// @brief Handles the setup of the pipes and redirections. Handles heredoc
/// as well.
/// @param mo_shell Pointer to the Mother Shell structure.
/// @return ERROR on error, NO_ERROR otherwise.
t_error	pipeline_setup(t_mo_shell *mo_shell)
{
	mo_shell->cmds_table = spltd_in_to_cmd_blocks(&mo_shell->splitted_input);
	fill_cmd_and_args(&mo_shell->cmds_table, &mo_shell->splitted_input);
	open_redir_files(&mo_shell->cmds_table, &mo_shell->splitted_input);
	//TODO Setup pipes and redirections from right to left, redirections steal the pipe
	//TODO Pop les nodes qui correspondent à la redirection pour pouvoir renseigner les arguments ensuite
	setup_redirections(&mo_shell->splitted_input, &mo_shell->cmds_table);
	return (NO_ERROR);
}

t_cmd	*spltd_in_to_cmd_blocks(t_block **head)
{
	t_block	*nav;
	t_cmd	*tmp;
	int		number_of_cmds;
	t_cmd	*ret;

	ret = NULL;
	tmp = NULL;
	number_of_cmds = 1;
	nav = *head;
	while (nav)
	{
		if (nav->type == PIPE)
			number_of_cmds++;
		nav = nav->next;
	}
	tmp = cmd_new(NULL);
	ret = tmp;
	number_of_cmds--;
	while (number_of_cmds > 0)
	{
		tmp = cmd_new(NULL);
		cmd_add_back(ret, tmp);
		number_of_cmds--;
	}
	return (ret);
}

/// @brief Opens files for the command blocks, handles several redirections.
/// @param cmd_head The command table list's head.
/// @param block_head The block list's head.
/// @return ERROR if file couldn't be opened, NO_ERROR otherwise.
t_error	open_redir_files(t_cmd **cmd_head, t_block **block_head)
{
			if (open_redir_i(cmd_head, block_head) == ERROR)
				return (ERROR);
			if (open_redir_o(cmd_head, block_head) == ERROR)
				return (ERROR);
	return (NO_ERROR);
}
