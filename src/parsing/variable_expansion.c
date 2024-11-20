/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:33:51 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/20 19:25:03 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/// @brief
/// @param var The name of the variable we want to get the index of
/// @param envp The environment in which we will look for the variable
/// @return The index of the variable if it exists, -1 if the variable doesn't
/// exists and -2 if there's no variable name provided.
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

char	*get_var_content(char *var_name, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (ft_strncmp(var_name, env[i], ft_strlen(var_name)))
		i++;
	if (env[i] == NULL)
		return (NULL);
	j = 0;
	while (env[i][j] != '=')
		j++;
	j++;
	return (ft_strdup(&env[i][j]));
}

/// @brief
/// @param ret
/// @param src
/// @param i
/// @param envp
/// @return
char	*var_expander(char *ret, char *src, int *i, char *envp[])
{
	(void)envp;
	char	*var_content;
	char	var_name[1024];
	int		j;

	j = 0;
	while (src && src[j] && src[j] != '$' &&!ft_is_ifs(src[j]))
	{
		var_name[j] = src[j];
		j++;
	}
	var_name[j] = '\0';
	var_content = get_var_content(var_name, envp);
	
	if (var_content)
	{
		ret = append(ret, var_content, ft_strlen(var_content));
		free(var_content);
	}
	*i += j;
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
/// @param mo_shell
char	*expand_variables(char *src, char *envp[], t_mo_shell *mo_shell)
{
	int		i;
	char	*ret;
	int		quotes;
	size_t	les_len;
	char	*les;

	les = ft_itoa(mo_shell->last_exit_status);
	les_len = ft_strlen(les);
	ret = str_init();
	quotes = 0;
	i = 0;
	while (src[i])
	{
		check_in_quotes(src[i], &quotes);
		if (quotes != 1 && '$' == src[i])
		{
			i++;
			if (src[i] == '$')
				i++;
			else if (src[i] == '?')
			{
				ret = append(ret, les, les_len);
				i++;
			}
			else
				ret = var_expander(ret, &src[i], &i, envp);
		}
		else
		{
			ret = append(ret, &src[i], 1);
			i++;
		}
	}
	free(les);
	return (ret);
}
