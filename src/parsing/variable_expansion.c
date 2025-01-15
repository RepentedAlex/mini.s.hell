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
	if (var_name[0] == '\0')
		return (NULL);
	while (env && env[i] && (ft_strncmp(var_name, env[i], \
		ft_strlen(var_name) + 1) != ('\0' - '=')))
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

char	*str_init(void)
{
	char	*ret;

	ret = malloc(sizeof(char));
	if (!ret)
		return (NULL);
	*ret = '\0';
	return (ret);
}

void	init_les(char **les, size_t *les_len, t_mo_shell *mo_shell)
{
	*les = ft_itoa(mo_shell->last_exit_status);
		if (!*les)
			*les = 0;
		*les_len = ft_strlen(*les);
}

int	get_var_len(char *src, t_mo_shell *mo_shell)
{
	int	i;
	int	ret;
	char	var_name[DEF_BUF_SIZ];
	char	*var_content;

	ft_bzero(var_name, DEF_BUF_SIZ);
	var_content = NULL;
	i = 0;
	while (src && src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
	{
		var_name[i] = src[i];
		i++;
	}
	var_content = get_var_content(var_name, mo_shell->shell_env);
	if (!var_content)
		return (0);
	ret = ft_strlen(var_content);
	free(var_content);
	return (ret);
}

/// @brief 
/// @param src
/// @param ret 
/// @param mo_shell 
/// @param les 
/// @return 
int make_expansion(char *src, char **ret, t_mo_shell *mo_shell, char **les)
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
	// res = get_var_len(&src[i], mo_shell);
	*ret = var_expander(*ret, &src[i], &res, mo_shell->shell_env);
	return(res);
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
