/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:51:38 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/08 18:51:41 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//apetitco
// TODO On peut se faire baiser parce que je regarde pas
// ce qu'il y a derrière le token
void	identify_tokens(t_token **head)
{
	t_token	*nav;

	nav = *head;
	if (!nav)
		return ;
	while (nav)
	{
		if (ft_strncmp(nav->str, "|", 1) == 0)
			nav->type = PIPE;
		if (ft_strncmp(nav->str, "<", 1) == 0)
			nav->type = REDIR_I;
		if (ft_strncmp(nav->str, ">", 1) == 0)
			nav->type = REDIR_O;
		if (ft_strncmp(nav->str, ">>", 2) == 0)
			nav->type = APPEND;
		if (ft_strncmp(nav->str, "<<", 2) == 0)
			nav->type = HEREDOC;
		nav = nav->next;
	}
}

/// @brief Breaks a string in an array of tokens.
/// @param data_env The input string.
/// @param data
/// @return A 2D array holding all the tokens + NULL pointer at the end.
void	tokeniser(t_shell_env *data)
{
	int	i;
	//LL OR ARRAY ?
	// apetitco: I guess LL is better because we might pop some
	// elements (such as redir) so it would be more convenient
	i = 0;
	while (data->buffer && is_ifs(data->buffer[i]))
		i++;
	while (data->buffer && data->buffer[i])
	{
		//TODO
		get_next_token(data->tokens, data->buffer, &i);
		i++;
	}
}
