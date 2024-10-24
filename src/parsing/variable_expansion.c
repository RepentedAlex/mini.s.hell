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

int	var_exst(char *var, char *envp[])
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

char	*var_expander(char *ret, char *src, int *i, char *envp[])
{
	int		var_index;
	char	*var_content;

	var_index = find_var(&src[*i], envp);
	if (var_index > -1)
	{
		var_content = ft_strchr(envp[var_index], '=') + 1;
		ret = append(ret, var_content, ft_strlen(var_content));
	}
	while (ft_is_alpha(src[++*i + 1]))
		src += 0;
	return (ret);
}

char	*str_init(void)
{
	char	*ret;

	ret = malloc(sizeof(char));
	if (!ret)
		return (NULL);
	*ret = '\0';
	return (ret);
}

/// @brief Takes a string and check if there are variables that
/// should be expanded
/// @param src The source string.
/// @param envp The environment variables.
char	*expand_variables(char *src, char *envp[])
{
	int		i;
	char	*ret;
	int		quotes;

	ret = str_init();
	quotes = 0;
	i = -1;
	while (src[++i])
	{
		check_in_quotes(src[i], &quotes);
		if (!quotes && '$' == src[i])
		{
			if (src[++i] == '$')
				i += 2;
			else
			{
				ret = var_expander(ret, src, &i, envp);
				continue ;
			}
		}
		ret = append(ret, &src[i], sizeof(char));
	}
	return (ret);
}
