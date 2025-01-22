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
		return (*value1 = err_msg(REO_STX_MSG, NULL), mo_shell->les = 2, true);
	if (*error_ret == 2)
		return (*value1 = err_msg(APP_STX_MSG, NULL), mo_shell->les = 2, true);
	if (*error_ret == 3)
		return (*value1 = err_msg(REO_STX_MSG, NULL), mo_shell->les = 2, true);
	if (*error_ret == 4)
		return (*value1 = err_msg(HD_STX_MSG, NULL), mo_shell->les = 2, true);
	if (*error_ret == 5)
		return (*value1 = err_msg(NEW_STX_MSG, NULL), mo_shell->les = 2, true);
	return (false);
}
