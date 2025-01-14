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
		i += 0;
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
	int		var_index;

	var_index = var_exst(var_name, envp);
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

bool	is_valid_variable_name(char *vr_name)
{
	int	i;

	i = 0;
	if (!vr_name[i] || (ft_isalpha(vr_name[i]) == false && vr_name[i] != '_'))
		return (false);
	i++;
	while (vr_name[i] && (ft_isalnum(vr_name[i]) || vr_name[i] == '_'))
		i++;
	if (!vr_name[i])
		return (true);
	return (false);
}

static void	update_env_var(char *arg, char *var_name, t_mo_shell *shell)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	i++;
	strip_quotes(arg);
	if (var_exst(var_name, shell->shell_env) == -1)
		shell->shell_env = add_str_to_array(shell->shell_env, arg);
	else
		update_var(var_name, &arg[i], shell->shell_env);
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
		while (args[args_iterator][i])
		{
			if (args[args_iterator][i] == '=')
			{
				i++;	//Faire gaffe, peutetre que ca fait nimp pour `C=`
				break ;
			}
			var_name[i] = args[args_iterator][i];
			i++;
		}

		if (!args[args_iterator][i])
		{
			args_iterator++;
			continue ;
		}

		if (is_valid_variable_name(var_name) == false)
		{
			args_iterator++;
			continue ;
		}

		update_env_var(args[args_iterator], var_name, mo_shell);
		args_iterator++;
	}
	return (0);
}
