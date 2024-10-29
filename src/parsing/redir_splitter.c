/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:44:05 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/21 18:44:10 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	for_heredoc(t_block **nav, t_block **tmp, int *i)
{
	*tmp = block_new(ft_strdup("<<"));
	(*tmp)->type = HEREDOC;
	block_add_after(*nav, *tmp);
	*tmp = block_new(ft_strdup(ft_strchr((*nav)->str, '<') + 2));
	(*tmp)->type = EOFHD;
	block_add_after((*nav)->next, *tmp);
	*i = 0;
	*nav = (*nav)->next;
	*nav = (*nav)->next;
}

void	for_append(t_block **nav, t_block **tmp, int *i)
{
	*tmp = block_new(ft_strdup(">>"));
	(*tmp)->type = APPEND;
	block_add_after(*nav, *tmp);
	*tmp = block_new(ft_strdup(ft_strchr((*nav)->str, '>') + 2));
	(*tmp)->type = OUTFILE;
	block_add_after((*nav)->next, *tmp);
	*i = 0;
	*nav = (*nav)->next;
	*nav = (*nav)->next;
}

void	for_redir_o(t_block **nav, t_block **tmp, int *i)
{
	*tmp = block_new(ft_strdup(">"));
	(*tmp)->type = REDIR_O;
	block_add_after(*nav, *tmp);
	*tmp = block_new(ft_strdup(ft_strchr((*nav)->str, '>') + 1));
	(*tmp)->type = OUTFILE;
	block_add_after((*nav)->next, *tmp);
	*i = 0;
	*nav = (*nav)->next;
	*nav = (*nav)->next;
}


t_error	lexcat_redir(t_block **head)
{
	t_block	*nav;

	nav = *head;
	while (nav)
	{
		if (!ft_strcmp(nav->str, ">>"))
		{
			nav->type = APPEND;
			nav->next->type = OUTFILE;
			nav = nav->next;
		}
		if (!ft_strcmp(nav->str, "<<"))
		{
			nav->type = HEREDOC;
			nav->next->type = EOFHD;
			nav = nav->next;
		}
		if (!ft_strcmp(nav->str, ">"))
		{
			nav->type = REDIR_O;
			nav->next->type = OUTFILE;
			nav = nav->next;
		}
		if (!ft_strcmp(nav->str, "<"))
		{
			nav->type = REDIR_I;
			nav->next->type = INFILE;
			nav = nav->next;
		}
		nav = nav->next;
	}
	return (NO_ERROR);
}
