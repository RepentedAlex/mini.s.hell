/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:46:31 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 15:46:34 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syntax_check_handler(t_mo_shell *mo_shell, int *error_ret, \
	t_error *value1)
{
	*error_ret = check_redir_syntax(&mo_shell->splitted_input);
	if (*error_ret == 1)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '>'\n"), mo_shell->last_exit_status = 2, true);
	if (*error_ret == 2)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '>>'\n"), mo_shell->last_exit_status = 2, true);
	if (*error_ret == 3)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '<'\n"), mo_shell->last_exit_status = 2, true);
	if (*error_ret == 4)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '<<'\n"), mo_shell->last_exit_status = 2, true);
	if (*error_ret == 5)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token 'newline'\n"), mo_shell->last_exit_status = 2, true);
	return (false);
}
