/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_inspection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:49:50 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/15 13:49:53 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_after_redir(char *str, int i)
{
	while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|')
	{
		if (ft_is_alpha(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	check_before_redir(char *str, int i)
{
	while (i >= 0 && str[i] != '<' && str[i] != '>' && str[i] != '|')
	{
		if (ft_is_alpha(str[i]))
			return (true);
		i--;
	}
	return (false);
}

t_error	check_redir_syntax(t_block **head)
{
	int		i;
	t_block	*nav;

	nav = *head;
	if (!nav)
		return (ERROR);
	while (nav != NULL)
	{
		i = 0;
		while (nav->str[i])
		{
			if (nav->str[i] == '>')
			{
				if (nav->str[i + 1] == '>')
				{
					// Check word.s before append redir
					if (check_before_redir(nav->str, i - 1) == false)
						return (ERROR);
					// Check word.s after append redir
					if (check_after_redir(nav->str, i + 2) == false)
						return (ERROR);
					i++;
				}
				else
				{
					// Check word.s before output redir
					if (check_before_redir(nav->str, i - 1) == false)
						return (ERROR);
					// Check word.s after output redir
					if (check_after_redir(nav->str, i + 1) == false)
						return (ERROR);
				}
			}
			else if (nav->str[i] == '<')
			{
				if (nav->str[i + 1] == '<')
				{
					// Check word.s before heredoc
					if (check_before_redir(nav->str, i - 1) == false)
						return (ERROR);
					// Check word.s after heredoc
					if (check_after_redir(nav->str, i + 2) == false)
						return (ERROR);
					i++;
				}
				else
				{
					// Check word.s before input redir
					if (check_before_redir(nav->str, i - 1) == false)
						return (ERROR);
					// Check word.s after input redir
					if (check_after_redir(nav->str, i + 1) == false)
						return (ERROR);
				}
			}
			i++;
		}
		nav = nav->next;
	}
	return (NO_ERROR);
}

bool	look_for_redir(t_block **head)
{
	t_block	*nav;

	nav = *head;
	if (nav == NULL)
		return (false);
	while (nav != NULL)
	{
		if (ft_strchr(nav->str, '<') || ft_strchr(nav->str, '>'))
			return (true);
		nav = nav->next;
	}
	return (false);
}

/// @brief Takes a list of t_block and create new nodes when it finds a '<', '<<', '>', '>>'.
/// @param head
/// @return
t_error	split_redir(t_block **head)
{
	t_block	*nav;
	t_block	*tmp;
	int		i;

	tmp = NULL;
	nav = *head;
	if (!nav)
		return (ERROR);
	while (nav != NULL)
	{
		if (ft_strchr(nav->str, '<') == NULL && ft_strchr(nav->str, '>') == NULL)
		{
			nav = nav->next;
			continue ;
		}
		// Check for heredoc
		if (ft_strncmp(ft_strchr(nav->str, '<'), "<<", 2) == 0)
		{
			tmp = block_new("<<");
			tmp->type = HEREDOC;
			block_add_after(nav, tmp);
			tmp = block_new(strdup(ft_strchr(nav->str, '<') + 2));	//TODO ft_strdup
			block_add_after(nav->next, tmp);
			i = 0;
			while (nav->str[i] && nav->str[i] != '<')
				i++;
			nav->str[i] = '\0';
			nav = nav->next;
			nav = nav->next;
			continue ;
		}
		// Check for append
		if (ft_strncmp(ft_strchr(nav->str, '>'), ">>", 2) == 0)
		{
			tmp = block_new(">>");
			tmp->type = APPEND;
			block_add_after(nav, tmp);
			tmp = block_new(strdup(ft_strchr(nav->str, '>') + 2));	//TODO ft_strdup
			block_add_after(nav->next, tmp);
			i = 0;
			while (nav->str[i] && nav->str[i] != '>')
				i++;
			nav->str[i] = '\0';
			nav = nav->next;
			nav = nav->next;
			continue ;
		}
		if (ft_strncmp(ft_strchr(nav->str, '>'), ">", 1) == 0)
		{
			tmp = block_new(">");
			tmp->type = REDIR_O;
			block_add_after(nav, tmp);
			tmp = block_new(strdup(ft_strchr(nav->str, '>') + 1));	//TODO ft_strdup
			block_add_after(nav->next, tmp);
			i = 0;
			while (nav->str[i] && nav->str[i] != '>')
				i++;
			nav->str[i] = '\0';
			nav = nav->next;
			nav = nav->next;
			continue ;
		}
		if (ft_strncmp(ft_strchr(nav->str, '<'), "<", 1) == 0)
		{
			tmp = block_new("<");
			tmp->type = REDIR_I;
			block_add_after(nav, tmp);
			tmp = block_new(strdup(ft_strchr(nav->str, '<') + 1));	//TODO ft_strdup
			block_add_after(nav->next, tmp);
			i = 0;
			while (nav->str[i] && nav->str[i] != '<')
				i++;
			nav->str[i] = '\0';
			nav = nav->next;
			nav = nav->next;
		}
	}
	return (NO_ERROR);
}
