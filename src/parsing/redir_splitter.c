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
	while ((*nav)->str[(*i)] && (*nav)->str[(*i)] != '<')
		(*i)++;
	(*nav)->str[(*i)] = '\0';
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
	while ((*nav)->str[(*i)] && (*nav)->str[(*i)] != '>')
		(*i)++;
	(*nav)->str[(*i)] = '\0';
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
	while ((*nav)->str[(*i)] && (*nav)->str[(*i)] != '>')
		(*i)++;
	(*nav)->str[(*i)] = '\0';
	*nav = (*nav)->next;
	*nav = (*nav)->next;
}

void	for_redir_i(t_block **nav, t_block **tmp, int *i)
{
	*tmp = block_new(ft_strdup("<"));
	(*tmp)->type = REDIR_I;
	block_add_after(*nav, *tmp);
	*tmp = block_new(ft_strdup(ft_strchr((*nav)->str, '<') + 1));
	(*tmp)->type = INFILE;
	block_add_after((*nav)->next, *tmp);
	*i = 0;
	while ((*nav)->str[(*i)] && (*nav)->str[(*i)] != '<')
		(*i)++;
	(*nav)->str[(*i)] = '\0';
	*nav = (*nav)->next;
	*nav = (*nav)->next;
}

/// @brief Takes a list of t_block and create new nodes when it finds a '<',
/// '<<', '>', '>>'.
/// @param head
/// @return
t_error	split_redir(t_block **head)
{
	t_block	*nav;
	t_block	*tmp;
	int		i;

	nav = *head;
	while (nav != NULL)
	{
		if (ft_strchr(nav->str, '<') == NULL && ft_strchr(nav->str, '>') \
			== NULL)
			nav = nav->next;
		else if (ft_strchr(nav->str, '<') && ft_strncmp(\
			ft_strchr(nav->str, '<'), "<<", 2) == 0)
			for_heredoc(&nav, &tmp, &i);
		else if (ft_strchr(nav->str, '>') && ft_strncmp(\
			ft_strchr(nav->str, '>'), ">>", 2) == 0)
			for_append(&nav, &tmp, &i);
		else if (ft_strchr(nav->str, '>') && ft_strncmp(\
			ft_strchr(nav->str, '>'), ">", 1) == 0)
			for_redir_o(&nav, &tmp, &i);
		else if (ft_strchr(nav->str, '<') && ft_strncmp(\
			ft_strchr(nav->str, '<'), "<", 1) == 0)
			for_redir_i(&nav, &tmp, &i);
	}
	return (NO_ERROR);
}
