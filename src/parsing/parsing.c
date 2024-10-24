/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:58:50 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/21 14:58:52 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syntax_check_handler(t_mo_shell *mo_shell, int *error_ret, \
	t_error *value1)
{
	*error_ret = check_redir_syntax(&mo_shell->splitted_input);
	if (*error_ret == 1)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '>'\n"), true);
	if (*error_ret == 2)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '>>'\n"), true);
	if (*error_ret == 3)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '<'\n"), true);
	if (*error_ret == 4)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '<<'\n"), true);
	if (*error_ret == 5)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token 'newline'\n"), true);
	split_redir(&mo_shell->splitted_input);
	return (false);
}

t_error	splitter(t_mo_shell *mo_shell)
{
	int		error_ret;
	t_error	sch_ret;

	error_ret = 0;
	if (look_for_pipes(&mo_shell->splitted_input) == true)
	{
		if (check_pipes_syntax(&mo_shell->splitted_input) == ERROR)
			return (printf("mini.s.hell: syntax error near unexpected \
token '|'\n"), ERROR);
		split_pipes(&mo_shell->splitted_input);
	}
	if (look_for_redir(&mo_shell->splitted_input) == true)
		if (syntax_check_handler(mo_shell, &error_ret, &sch_ret))
			return (sch_ret);
	block_string_tidyer(&mo_shell->splitted_input);
	split_spaces(&mo_shell->splitted_input);
	//TODO Remove quotes
	if (check_not_dirfile(&mo_shell->splitted_input) == ERROR)
		return (ERROR);
	return (NO_ERROR);
}

t_error	parsing(t_mo_shell *mo_shell)
{
	if (check_open_quotes(mo_shell->og_input) == ERROR)
		return (printf("mini.s.hell: quotes are not closed\n"), ERROR);
	mo_shell->clean_input = string_tidyer(mo_shell->og_input);
	if (mo_shell->clean_input == NULL)
		return (ERROR);
	mo_shell->expanded_input = expand_variables(mo_shell->clean_input, \
		mo_shell->shell_env);
	mo_shell->splitted_input = block_setup_first(mo_shell);
	if (splitter(mo_shell))
		return (ERROR);
	return (NO_ERROR);
}
