/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:33:51 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/29 19:02:51 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/// @brief
/// @param var The name of the variable we want to get the index of
/// @param envp The environment in which we will look for the variable
/// @return The index of the variable if it exist, -1 if the variable doesn't
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
/// @param ret
/// @param src
/// @param i
/// @param envp
/// @return
char	*var_expander(char *ret, char *src, int *i, char *envp[])
{
	char	*var_content;
	char	var_name[DEF_BUF_SIZ];
	int		j;

	j = -1;
	if (src && src[0] && ft_isdigit(src[0]))
		return (*i += 1, ret);
	while (src && src[++j] && src[j] != '$' && (ft_isalnum(src[j]) || \
		src[j] == '_'))
		var_name[j] = src[j];
	var_name[j] = '\0';
	if (ft_strlen(var_name) == 0)
		return (ret = append(ret, "$", 1), ret);
	var_content = get_var_content(var_name, envp);
	if (!var_content)
	{
		*i += j;
		return (ret);
	}
	ret = append(ret, var_content, ft_strlen(var_content));
	free(var_content);
	*i += j;
	return (ret);
}

/// @brief 
/// @param src
/// @param ret 
/// @param mo_shell 
/// @param les 
/// @return 
int	make_expansion(char *src, char **ret, t_mo_shell *mo_shell, char **les)
{
	size_t	les_len;
	int		res;
	int		i;

	i = 1;
	res = 0;
	init_les(les, &les_len, mo_shell);
	if (!src[i] || src[i] == '\'' || src[i] == '"')
		return (*ret = append(*ret, "$", 1), 0);
	if (ft_is_ifs(src[i]) == true)
		return (*ret = append(*ret, "$ ", 2), 1);
	if (src[i] == '\'' || src[i] == '\"')
		return (0);
	if (src[i] == '$')
		return (*ret = append(*ret, "$$", 2), 1);
	if (src[i] == '?')
		return (*ret = append(*ret, *les, les_len), ((int)les_len - 1));
	*ret = var_expander(*ret, &src[i], &res, mo_shell->shell_env);
	return (res);
}

/// @brief Takes a string and check if there are variables that
/// should be expanded
/// @param src The source string.
/// @param mo_shell
char	*expand_variables(char *src, t_mo_shell *mo_shell)
{
	char	*ret;
	char	*les;
	int		i;
	int		quotes;

	les = NULL;
	ret = str_init();
	quotes = 0;
	i = -1;
	while (src && src[++i])
	{
		check_in_quotes(src[i], &quotes);
		if (quotes != 1 && src[i] == '$')
			i += make_expansion(&src[i], &ret, mo_shell, &les);
		else
		{
			ret = append(ret, &src[i], 1);
			if (!ret)
				return (free(les), NULL);
		}
	}
	if (les)
		free(les);
	return (ret);
}
