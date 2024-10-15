/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:33:51 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/14 14:33:53 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_var_exists(char *var, char *envp[])
{
	int		i;
	int		j;
	char	*tmp;

	tmp = var;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == tmp[j])
			j++;
		if (tmp[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}
