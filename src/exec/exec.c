/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:39:02 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/23 18:39:05 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"

void	setup_redirections(t_block **block_head, t_cmd **cmd_head)
{
	t_block	*nav_block;
	t_cmd	*nav_cmd;

	nav_block = block_goto_last(*block_head);
	nav_cmd = cmd_goto_last(*cmd_head);

	while (nav_cmd)
	{
		while (nav_block && ft_strcmp(nav_block->str, nav_cmd->cmd))
		{
			if (nav_block->type >= 2 && nav_block->type <= 5) //Si on tombe sur une redirection ('<', '>', '<<', '>>'), alors on redirige l'entrée ou la sortie sur le fichier pointé
			{ // REMINDER : Les redirections VOLENT les pipes (oui, sans vergogne aucune)
				//TODO GÉRER LA REDIR
				//TODO GÉRER LE HEREDOC
			}
			nav_block = nav_block->prev;
		}
		//À chaque pipe, rediriger la sortie de la commande précédente en entrée de la commande actuelle
		//TODO GÉRER LE PIPE
		nav_cmd = nav_cmd->prev;
	}

}

char	**for_first_arg(char *str)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 2);
	if (!ret)
	{
		return (NULL);
	}
	ret[0] = ft_strdup(str);
	ret[1] = NULL;
	return (ret);
}

char	**add_str_to_array(char **array, char *str)
{
	char	**nav;
	char	**ret;
	int		i;

	ret = NULL;
	nav = array;
	if (!nav)
		return (for_first_arg(str));
	i = 0;
	while (nav[i] != NULL)
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (NULL);
	i = -1;
	while (array[++i] != NULL)
		ret[i] = ft_strdup(array[i]);
	ret[i] = ft_strdup(str);
	ret[i + 1] = NULL;
	(free_2d_tab(array), array = NULL);
	return (ret);
}

void	renseign_fields(t_cmd **cmd_head, t_block **block_head)
{
	t_block	*nav_block;
	t_cmd	*nav_cmd;
	bool	block_has_cmd;

	nav_cmd = *cmd_head;
	nav_block = *block_head;
	while (nav_cmd)
	{
		block_has_cmd = false;
		while (nav_block && nav_block->type != PIPE)
		{
			if (!block_has_cmd && nav_block->type == RAW)
			{
				block_has_cmd = true;
				nav_cmd->cmd = ft_strdup(nav_block->str);
				nav_block->type = CMD;
				nav_block = nav_block->next;
			}
			else if (block_has_cmd && nav_block->type == RAW)
			{
				nav_cmd->args = add_str_to_array(nav_cmd->args, nav_block->str);
				nav_block = nav_block->next;
			}
			else if (nav_block->type >= 2 && nav_block->type <= 5)
			{
				if (nav_block->type == REDIR_O)
				{
					nav_block = nav_block->next;
					if (nav_cmd->fd_o >= 0)
						(close(nav_cmd->fd_o), nav_cmd->fd_o = 0);
					nav_cmd->fd_o = open(nav_block->str, O_RDWR | O_CREAT | O_TRUNC, 0666);
				}
				else if (nav_block->type == APPEND)
				{
					nav_block = nav_block->next;
					if (nav_cmd->fd_o >= 0)
						(close(nav_cmd->fd_o), nav_cmd->fd_o = 0);
					nav_cmd->fd_o = open(nav_block->str, O_RDWR | O_APPEND | O_CREAT, 0666);
				}
				else if (nav_block->type == REDIR_I)
				{
					nav_block = nav_block->next;
					if (nav_cmd->fd_i >= 0)
						(close(nav_cmd->fd_i), nav_cmd->fd_i = 0);
					nav_cmd->fd_i = open(nav_block->str, O_RDWR);
				}
				else if (nav_block->type == HEREDOC)
				{
					nav_block = nav_block->next;
					if (nav_cmd->fd_i >= 0)
						(close(nav_cmd->fd_i), nav_cmd->fd_i = 0);
					nav_cmd->fd_i = open("heredoc", O_RDWR | O_CREAT, 0666);
					//TODO Fill heredoc
					// fill_heredoc();
				}
				nav_block = nav_block->next;
			}
		}
		if (nav_block)
			nav_block = nav_block->next;
		nav_cmd = nav_cmd->next;
	}
}

t_cmd *splitted_input_to_cmd_blocks(t_block **head)
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

void	execute_cl(t_mo_shell *mo_shell)
{
	t_block	*nav;
	t_cmd	*to_launch;

	nav = mo_shell->splitted_input;
	if (!nav)
		return ;
	mo_shell->cmds_table = splitted_input_to_cmd_blocks(&mo_shell->splitted_input);
	renseign_fields(&mo_shell->cmds_table, &mo_shell->splitted_input);
	// create_outfiles(&mo_shell->cmds_table);
	//TODO Setup pipes and redirections from right to left, redirections steal the pipe
	//TODO Pop les nodes qui correspondent à la redirection pour pouvoir renseigner les arguments ensuite
	setup_redirections(&mo_shell->splitted_input, &mo_shell->cmds_table);

	//TODO Renseigner le field arguments de chaque t_cmd


	to_launch = mo_shell->cmds_table;
	//TODO Execute from left to right
	while (to_launch)
	{
		if (is_builtin(to_launch->cmd) == true)
		{
			//exec builtin
			launch_builtins(to_launch);
		}
		else
		{
			//execve
		}
		to_launch = to_launch->next;
	}
	to_launch = mo_shell->cmds_table;
	while (to_launch)
	{
		if (to_launch->fd_i >= 0)
			(close(to_launch->fd_i), to_launch->fd_i = -2);
		if (to_launch->fd_o >= 0)
			(close(to_launch->fd_o), to_launch->fd_o = -2);
		to_launch = to_launch->next;
	}
}
