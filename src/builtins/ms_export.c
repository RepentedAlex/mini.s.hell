/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:55:09 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/26 18:08:26 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

static void	strip_quotes(char *str)
{
	int	i;
	int	quotes;

	quotes = 0;
	i = -1;
	while (str[++i] != '=')
	{
		i += 0;
	}
	i++;
	if (str[i] == '\'')
	{
		quotes = 1;
		ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i]));
	}
	else if (str[i] == '\"')
	{
		quotes = 2;
		ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i]));
	}
	while (str[i])
	{
		check_in_quotes(str[i], &quotes);
		i++;
	}
	if ((str[i - 1] == '\'' || str[i - 1] == '\"') && quotes == 0)
		str[i - 1] = '\0';
}

t_error	update_var(char *var_name, char *var_content, char *envp[])
{
	char	*tmp;
	char	*equal;
	int		var_index;

	var_index = var_exst(var_name, envp);
	// tmp = malloc(sizeof(char) * (ft_strlen(var_name) + ft_strlen(var_content) + 2));
	// if (!tmp)
	// 	return (ERROR);
	equal = ft_strdup("=");
	if (!equal)
		return (ERROR);
	tmp = ft_strdup(var_name);
	if (!tmp)
		return (ERROR);
	tmp = append(tmp, "=", 1);
	if (!tmp)
		return (ERROR);
	tmp = append(tmp, var_content, ft_strlen(var_content));
	if (!tmp)
		return (ERROR);
	free(envp[var_index]);
	envp[var_index] = NULL;
	envp[var_index] = tmp;
	return (0);
}

bool	is_valid_variable_name(char *var_name)
{
	int	i;

	i = 0;
	if (!var_name[i] || (ft_isalpha(var_name[i]) == false && var_name[i] != '_'))
		return (false);
	i++;
	while (var_name[i] && (ft_isalnum(var_name[i]) || var_name[i] == '_'))
		i++;
	if (!var_name[i])
		return (true);
	return (false);
}

/// @brief Sets variable in the environment
/// @param args
/// @param cmd
/// @return
int	ms_export(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		i;
	int		args_iterator;
	char	var_name[DEF_BUF_SIZ];

	(void)cmd;
	(void)args;
	args_iterator = 1;
	ft_bzero(var_name, DEF_BUF_SIZ);
	while (args[args_iterator] != NULL)
	{
		i = 0;
		while (args[args_iterator][i] && args[args_iterator][i] != '=')
		{
			var_name[i] = args[args_iterator][i];
			i++;
		}
		if (is_valid_variable_name(var_name) == false)
				break ;
		if (args[args_iterator][i] != '=')
			{
				printf("No value to assign to variable $%s\n", var_name);
				break ;
			}
		i++;
		strip_quotes(args[args_iterator]);
		if (var_exst(var_name, mo_shell->shell_env) == -1)
			mo_shell->shell_env = add_str_to_array(mo_shell->shell_env, args[args_iterator]);
		else
			update_var(var_name, &args[args_iterator][i], mo_shell->shell_env);
		args_iterator++;
	}
	return (0);
}
