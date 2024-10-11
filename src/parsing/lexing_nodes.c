/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:13:12 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/10 14:13:16 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_lex_token(char *str)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->str = str;
	node->type = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_token	*lex_goto_last(t_token *head)
{
	t_token	*nav;

	nav = head;
	if (nav == NULL)
		return (NULL);
	while (nav->next)
		nav = nav->next;
	return (nav);
}

t_error	lex_add_back(t_token **head, t_token *node)
{
	t_token	*tail;

	tail = lex_goto_last(*head);
	if (tail == NULL)
		*head = node;
	else
	{
		tail->next = node;
		node->prev = tail;
	}
	return (NO_ERROR);
}

int	get_token_len(char *str)
{
	int	i;
	int	quotes;

	quotes = 0;
	i = -1;
	while (str[++i] && (quotes == 0 && (ft_is_ifs(str[i]) || ft_is_symbol(&str[i]))))
	{
		check_in_quotes(str[i], &quotes);
		if (quotes == 0 && (ft_is_ifs(str[i]) || ft_is_symbol(&str[i])))		//Si on a un whitespace ou |, <, <<, >>, > hors quotes
			break ;
	}
	return (i);
}

char	*split_tok(char *str, int *index)
{
	int		len;
	int		i;
	char	*ret;
	(void)*index;

	len = 0;
	i = 0;
	len = get_token_len(str);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[len] = '\0';
	// if (ft_strcmp(ret))
	// *index += i;
	return (ret);




	// int	i;
	// int	quotes;
	//
	// quotes = 0;
	// i = 0;
	// while (str[i])
	// {
	// 	if (quotes == 0 && str[i] == '\'')
	// 		quotes = 1;
	// 	if (quotes == 0 && str[i] == '"')
	// 		quotes = 2;
	// 	else if ((quotes == 1 && str[i] == '\'') || (quotes == 2 && str[i] == '"'))
	// 		quotes = 0;
	// 	if ((!quotes && ft_is_ifs(str[i])))				//Breaks if space outside of quotes
	// 		break ;
	// 	if (!quotes && ft_is_symbol(&str[i]) == 1)			//Breaks if | < > << >> outside of quotes
	// 	{
	// 		break ;
	// 	}
	// 	if (!quotes && ft_is_symbol(&str[i]) == 2)
	// 	{
	// 		i++;
	// 		break ;
	// 	}
	// 	i++;
	// }
	// str[i] = '\0';
	// *index += i;
	// return (str);
}

/// @brief 
/// @param head 
/// @param str
/// @param index
/// @param i
void	get_next_token(t_token **head, char *str, int *index)
{
	int		i;
	t_token	*nav;
	char	*tmp;

	i = 0;
	while (str && ft_is_ifs(str[*index]))
		i += 1;
	tmp = split_tok(&str[*index], index);
	nav = new_lex_token(tmp);
	if (nav == NULL)
		return ;
	lex_add_back(head, nav);
}
