/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:43:32 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/16 23:43:32 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtins.h"

int	ms_export_check_options(char **args, int *iterator)
{
	if (args && args[*iterator] && args[*iterator][0] == '-')
		return (printf("%s: invalid option\n", args[*iterator]), 2);
	return (0);
}
