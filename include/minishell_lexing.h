/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexing.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:45:08 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/10 13:45:15 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LEXING_H
#define MINISHELL_LEXING_H
#include <minishell_types.h>

// == == == ENUMS == == ==



// == == == == STRUCTURES == == ==



// == == == FONCTIONS == == ==

void tokeniser(t_mo_shell *data);

// Linked list
t_token	*new_lex_token(char *str);
void	get_next_token(t_token **head, char *str, int *i);
void	identify_tokens(t_token **head);

#endif
