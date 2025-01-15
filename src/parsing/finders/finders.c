/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:36:03 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 22:36:25 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/// @brief
/// @param src The name of the variable we want to find
/// @param envp The environment in which we will look for the variable
/// @return The environment index of the variable if it exists, -1 otherwise
int	find_var(char *src, char *envp[])
{
	int		i;
	char	var_name[1024];
	int		var_index;

	i = 0;
	while (ft_isalpha(src[i]))
	{
		var_name[i] = src[i];
		i++;
	}
	var_name[i] = '\0';
	var_index = var_exst(var_name, envp);
	return (var_index);
}
