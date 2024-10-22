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
#include "libft.h"

int	check_if_var_exists(char *var, char *envp[])
{
	int		i;
	int		j;
	char	*tmp;

	tmp = var;
	if (var[0] == '\0')
		return (-2);
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

/// @brief Takes a string and check if there are variables that
/// should be expanded
/// @param src The source string.
/// @param envp The environment variables.
char	*expand_variables(char *src, char *envp[])
{
	int		i;
	int		j;
	int		quotes;
	char	current_var[1024];
	char	*ret;

	ret = malloc(sizeof(char));
	if (!ret)
		return (NULL);
	ft_memset(current_var, 0, sizeof(char) * 1024);
	ft_memset(ret, 0, sizeof(char));
	quotes = 0;
	i = 0;
	while (src[i])
	{
		check_in_quotes(src[i], &quotes);
		if (quotes != 1 && src[i] == '$')
		{
			if (src[i + 1] == '$')
			{
				i += 2;
				continue ;
			}
			j = 0;
			while (src[i + ++j] && ft_is_alpha(src[i + j]))
				current_var[j - 1] = src[i + j];
			current_var[j] = '\0';
			if (check_if_var_exists(current_var, envp) > -1)
			{
				ret = append(ret, &envp[check_if_var_exists(current_var, envp)][j],  \
					ft_strlen(&envp[check_if_var_exists(current_var, envp)][j]));		//TODO switch to ft_str_append
				i++;
				while (ft_is_alpha(src[i]))
					i++;
				continue ;
			}
			i++;
			while (ft_is_alpha(src[i]) || ft_is_ifs(src[i]))
				i++;
			continue ;
		}
		ret = append(ret, &src[i], sizeof(char));					// TODO Szitch to ft_str_append()
		i++;
	}
	return (ret);
}
