/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:27:58 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/10 12:28:06 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Checks if quotes are closed if there are some in the string.
/// @param str The line of command.
/// @return NO_ERROR if quotes are closed, ERROR if they are left open.
t_error	check_open_quotes(const char *str)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (str && str[++i])
	{
		if (!quotes && str[i] == '\"')
			quotes = 2;
		else if (!quotes && str[i] == '\'')
			quotes = 1;
		else if ((quotes == 1 && str[i] == '\'') || \
			(quotes == 2 && str[i] == '\"'))
			quotes = 0;
	}
	if (!quotes)
		return (NO_ERROR);
	return (ERROR);
}
