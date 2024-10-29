/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:22:22 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/15 13:22:25 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_block	*block_setup_first(t_mo_shell *mo_shell)
{
	t_block	*block;

	block = malloc(sizeof(t_block));
	if (!block)
		return (NULL);
	block->str = ft_strdup(mo_shell->expanded_input);
	if (!block->str)
		return (NULL);
	block->next = NULL;
	block->prev = NULL;
	block->type = 0;
	return (block);
}

void	for_space(t_block *nav)
{
	t_block	*tmp;
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (nav->str[i])
	{
		check_in_quotes(nav->str[i], &quotes);
		if (!quotes && !ft_is_symbol(&nav->str[i]) && !ft_is_ifs(nav->str[i]))
		{
			while (nav->str[i] && nav->str[i] != '>' && nav->str[i] != '<' && nav->str[i] != '|' && !ft_is_ifs(nav->str[i]))
				i++;
			if (ft_is_ifs(nav->str[i]))
			{
				nav->str[i] = '\0';
				i++;
				while (nav->str[i] && ft_is_ifs(nav->str[i]))
					i++;
				tmp = block_new(ft_strdup(&nav->str[i]));
				block_add_after(nav, tmp);
			}
			else if (nav->str[i] == '>' || nav->str[i] == '<')
			{
				tmp = block_new(ft_strdup(&nav->str[i]));
				block_add_after(nav, tmp);
				nav->str[i] = '\0';
			}
			break ;
		}
		if (!quotes && ft_is_ifs(nav->str[i]))
		{
			tmp = block_new(ft_strdup(&nav->str[i + 1]));
			tmp->type = RAW;
			block_add_after(nav, tmp);
			i = 0;
			while (nav->str[i] && nav->str[i] != ' ' && nav->str[i] != '\t' \
				&& nav->str[i] != '\n' && nav->str[i] != '<' && nav->str[i] != '>')
				i++;
			nav->str[i] = '\0';
			break ;
		}
		if (!quotes && !ft_strncmp(&nav->str[i], "<<", 2))
		{
			nav->type = HEREDOC;
			tmp = block_new(ft_strdup(&nav->str[2]));
			tmp->type = EOFHD;
			block_add_after(nav, tmp);
			i = 2;
			while (nav->str[i] && nav->str[i] != ' ' && nav->str[i] != '\t'
				&& nav->str[i] != '\n' && nav->str[i] != '<' && nav->str[i] != '>')
				i++;
			if (nav->str[i])
			{
				tmp = block_new(ft_strdup(&nav->str[i]));
				tmp->type = RAW;
				block_add_after(nav->next, tmp);
				nav->str[2] = '\0';
				nav->next->str[i - 2] = '\0';
			}
			nav->str[2] = '\0';
			break ;
		}
		if (!quotes && !ft_strncmp(&nav->str[i], ">>", 2))
		{
			nav->type = APPEND;
			tmp = block_new(ft_strdup(&nav->str[2]));
			tmp->type = OUTFILE;
			block_add_after(nav, tmp);
			i = 2;
			while (nav->str[i] && nav->str[i] != ' ' && nav->str[i] != '\t'
				&& nav->str[i] != '\n' && nav->str[i] != '<' && nav->str[i] != '>')
				i++;
			if (nav->str[i])
			{
				tmp = block_new(ft_strdup(&nav->str[i]));
				tmp->type = RAW;
				block_add_after(nav->next, tmp);
				nav->str[2] = '\0';
				nav->next->str[i - 2] = '\0';
			}
			nav->str[2] = '\0';
			break ;
		}
		if (!quotes && !ft_strncmp(&nav->str[i], ">", 1))
		{
			nav->type = REDIR_O;
			tmp = block_new(ft_strdup(&nav->str[1]));
			tmp->type = OUTFILE;
			block_add_after(nav, tmp);
			i = 1;
			while (nav->str[i] && nav->str[i] != ' ' && nav->str[i] != '\t'
				&& nav->str[i] != '\n' && nav->str[i] != '<' && nav->str[i] != '>')
				i++;
			if (nav->str[i])
			{
				tmp = block_new(ft_strdup(&nav->str[i]));
				tmp->type = RAW;
				block_add_after(nav->next, tmp);
				nav->str[1] = '\0';
				nav->next->str[i - 1] = '\0';
			}
			nav->str[1] = '\0';
			break ;
		}
		if (!quotes && !ft_strncmp(&nav->str[i], "<", 1))
		{
			nav->type = REDIR_I;
			tmp = block_new(ft_strdup(&nav->str[1]));
			tmp->type = INFILE;
			block_add_after(nav, tmp);
			i = 1;
			while (nav->str[i] && nav->str[i] != ' ' && nav->str[i] != '\t'
				&& nav->str[i] != '\n' && nav->str[i] != '<' && nav->str[i] != '>')
				i++;
			if (nav->str[i])
			{
				tmp = block_new(ft_strdup(&nav->str[i]));
				tmp->type = RAW;
				block_add_after(nav->next, tmp);
				nav->str[1] = '\0';
				nav->next->str[i - 1] = '\0';
			}
			break ;
		}
		else
		{
			while (nav->str[i] && nav->str[i] != ' ' && nav->str[i] != '\t'
			&& nav->str[i] != '\n' && nav->str[i] != '<' && nav->str[i] != '>')
				i++;
			if (nav->str[i])
			{
				if (nav->str[i] != ' ' && nav->str[i] != '\t' && nav->str[i] != '\n')
					tmp = block_new(ft_strdup(&nav->str[i + 1]));
				else
					tmp = block_new(ft_strdup(&nav->str[i]));
				tmp->type = RAW;
				block_add_after(nav, tmp);
				nav->str[i] = '\0';
			}
			break ;
		}
		i++;
	}
}

t_error	split_spaces(t_block **head)
{
	t_block	*nav;

	nav = *head;
	if (!nav)
		return (ERROR);
	while (nav != NULL)
	{
		if (nav->type == RAW)
			for_space(nav);
		nav = nav->next;
	}
	return (NO_ERROR);
}
