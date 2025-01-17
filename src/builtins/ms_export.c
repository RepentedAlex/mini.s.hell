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

/// @brief Updates the content of an existing environment variable in the
/// `envp` array.
/// The environment variable is located by its name, and its value is updated
/// with the provided content.
/// @param var_name The name of the environment variable to be updated.
/// @param var_content The new content (value) for the environment variable.
/// @param envp The environment array where the variable is stored.
/// @return `NO_ERROR` if the variable is successfully updated, otherwise
/// `ERROR` in case of memory allocation failures or other errors.
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

/// @brief Updates an environment variable in the shell's environment array.
/// If the variable does not exist, it is added to the environment; if it exists
/// , its value is updated.
/// @param arg The argument in the format `VAR=value` that contains the
/// environment variable and its new value.
/// @param var_name The name of the environment variable to be updated or added.
/// @param shell The shell's context, which contains the environment array
/// (`shell_env`).
/// @return `NO_ERROR` if the environment variable is successfully updated or
/// added, otherwise `ERROR`.
static	t_error	update_env_var(char *arg, char *var_name, t_mo_shell *shell)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	i++;
	tmp = &arg[i];
	tmp2 = ft_strdup(var_name);
	tmp2 = append(tmp2, "=", 1);
	if (var_exst(var_name, shell->shell_env) == -1)
	{
		tmp2 = append(tmp2, tmp, ft_strlen(tmp));
		add_str_to_ra(&shell->shell_env, tmp2);
		if (!shell->shell_env)
			return (free(tmp2), ERROR);
	}
	else
		update_var(var_name, tmp, shell->shell_env);
	return (free(tmp2), NO_ERROR);
}

/// @brief Iterates through a string to extract a variable name from an argument
/// in the format `VAR=value`.
/// @param args An array of strings representing the arguments passed to the
/// command.
/// @param i A pointer to the index of the current character being processed in
/// the argument.
/// @param args_iterator The index of the current argument being processed in
/// the `args` array.
/// @param var_name A buffer where the variable name is stored as it is
/// extracted from the argument.
/// @return `true` if the `=` character (indicating the end of the variable
/// name) is found, otherwise `false`.
bool	iterate_through_str(char **args, int *i, int args_iterator, \
						char var_name[DEF_BUF_SIZ])
{
	if (args[args_iterator][(*i)] == '=')
	{
		(*i)++;
		return (true);
	}
	var_name[(*i)] = args[args_iterator][(*i)];
	return (false);
}

static int	check_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (printf("export: `': not a valid identifier\n"), 1);
	if (str[i] == '=' || ft_isdigit(str[i]))
		return (printf("export: %s: not a valid identifier\n", str), 1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (printf("export: %s: not valid identifier\n", str), 1);
		i++;
	}
	return (0);
}

/// @brief Exports environment variables based on the provided arguments.
/// @param args An array of strings representing the arguments passed to
/// the `export` command, where each argument is a variable
/// assignment (`VAR=value`).
/// @param mo_shell A pointer to the shell environment structure, used for
/// storing and updating environment variables.
/// @param cmd A pointer to the command structure, unused in the current
/// implementation.
/// @return 0 if the operation is successful, or -1 if there is an error while
/// updating the environment variables.
int	ms_export(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		i;
	int		args_iterator;
	char	var_name[DEF_BUF_SIZ];
	int		ret;

	(void)cmd;
	ret = 0;
	args_iterator = 1;
	ret = ms_export_check_options(args, &args_iterator);
	if (ret)
		return (ret);
	while (args[args_iterator] != NULL)
	{
		(ft_bzero(var_name, DEF_BUF_SIZ), i = -1);
		ret = check_valid_identifier(args[args_iterator]);
		if (!ret)
		{
			while (args[args_iterator][++i])
				if (iterate_through_str(args, &i, args_iterator, var_name))
					break ;
			if (update_env_var(args[args_iterator], var_name, mo_shell) == ERROR)
				return (-1);
		}
		args_iterator++;
	}
	return (NO_ERROR);
}
