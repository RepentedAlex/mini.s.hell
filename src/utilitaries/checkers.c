/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:35:25 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 13:35:29 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(t_mo_shell *mo_shell)
{
	if (!mo_shell->og_input)
		return (0);
	if (mo_shell->og_input[0] == '!' && !mo_shell->og_input[1])
	{
		mo_shell->les = 1;
		return (1);
	}
	if (mo_shell->og_input[0] == '\0' || !words_in_str(mo_shell->og_input))
	{
		mo_shell->les = 0;
		return (1);
	}
	if (*mo_shell->og_input)
		add_history(mo_shell->og_input);
	return (2);
}

bool	string_is_only_ifs(const char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_is_ifs(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	words_in_str(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == ':' && flag == 0)
			flag = 1;
		else if (str[i] == ':' && flag == 1)
			return (true);
		if (str[i] != ':')
			return (true);
		i++;
	}
	return (false);
}
