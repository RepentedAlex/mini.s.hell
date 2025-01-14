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

/// @brief Removes quotes around the value of a string, specifically handling
/// single (`'`) and double (`"`) quotes.
/// This function modifies the input string by stripping any leading and
/// trailing quotes and adjusting the content accordingly.
/// @param str The string to process. The string is modified in-place.
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
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	i++;
	strip_quotes(arg);
	if (var_exst(var_name, shell->shell_env) == -1)
	{
		add_str_to_array(&shell->shell_env, arg);
		if (!shell->shell_env)
			return (ERROR);
	}
	else
		update_var(var_name, &arg[i], shell->shell_env);
	return (NO_ERROR);
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
bool iterate_through_str(char **args, int *i, int args_iterator, \
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

	(void)cmd;
	(void)args;
	args_iterator = 1;
	ft_bzero(var_name, DEF_BUF_SIZ);
	while (args[args_iterator] != NULL)
	{
		i = -1;
		while (args[args_iterator][++i])
			if (iterate_through_str(args, &i, args_iterator, var_name))
				break ;
		if (!args[args_iterator][i] && args_iterator++)
			continue ;
		if (is_valid_variable_name(var_name) == false && args_iterator++)
			continue ;
		if (update_env_var(args[args_iterator], var_name, mo_shell) == ERROR)
			return (-1);
		args_iterator++;
	}
	return (NO_ERROR);
}
