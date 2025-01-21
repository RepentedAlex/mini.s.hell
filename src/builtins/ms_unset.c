/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:40:39 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/26 18:15:12 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/// @brief Moves the variables in the environment array to remove the variable
/// at the specified index.
/// @param var_index The index of the variable to be removed from the
/// environment.
/// @param env The environment array of variables (modified in place).
/// @param var_after The number of variables after the one being removed, used
/// to determine the shift size.
/// @return This function has no return value. It modifies the environment array
/// in place.
void	move_var_in_env(int var_index, char **env, int var_after)
{
	free(env[var_index]);
	env[var_index] = NULL;
	ft_memmove(&env[var_index], &env[var_index + 1], sizeof(char *) \
		* (var_after + 1));
}

bool	check_valid_identifier(char *str, t_cmd *cmd, char **env)
{
	int	i;

	((void)cmd, (void)env);
	i = 0;
	if (str[i] == '\0')
		return (printf("export: `': not a valid identifier\n"), false);
	if (str[i] == '=' || ft_isdigit(str[i]))
		return (printf("export: %s: not a valid identifier\n", str), false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (printf("export: %s: not valid identifier\n", str), false);
		i++;
	}
	return (true);
}

void	init_ms_unset(t_mo_shell *mo_shell, int *args_iterator, char ***env)
{
	*env = mo_shell->shell_env;
	*args_iterator = 1;
}

/// @brief Removes environment variables specified in the arguments from the
/// shell's environment.
/// @param args Array of arguments where each entry (after the first) is a
/// variable name to unset.
/// @param mo_shell Pointer to the shell structure containing the environment
/// variables.
/// @param cmd Pointer to the command structure (unused in this function).
/// @return Returns 0 on success. Prints an error message and returns 1 if an
/// invalid identifier is encountered.
int	ms_unset(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		args_iterator;
	int		var_index;
	char	**env;
	int		var_after;

	init_ms_unset(mo_shell, &args_iterator, &env);
	while (args && args[args_iterator])
	{
		if (check_valid_identifier(args[args_iterator], cmd, env) == true)
		{
			var_index = var_exst(args[args_iterator], env);
			if (var_index == -1)
				return (0);
			var_after = 0;
			while (env[var_index + 1 + var_after] != NULL)
				var_after++;
			if (!var_after)
				(free(env[var_index]), env[var_index] = NULL);
			else
				move_var_in_env(var_index, env, var_after);
		}
		args_iterator++;
	}
	return (0);
}
