/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:12:03 by llabonde          #+#    #+#             */
/*   Updated: 2024/11/26 16:04:05 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/// @brief Checks if the given string represents a valid number consisting of
/// only digits.
/// @param s The string to check.
/// @return Returns true if the string contains only digit characters;
/// otherwise, returns false.
static bool	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

/// @brief Skips leading spaces in the given string and determines the sign of
/// the number.
/// Updates the index to point to the first non-space, non-sign character.
/// @param s The string to process for skipping spaces and determining the sign.
/// @param i A pointer to the index variable to update as spaces and sign
/// characters are skipped.
/// @param sign A pointer to the variable to store the sign of the number
/// (1 for positive, -1 for negative).
static void	ft_skip_spaces_and_get_sign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

/// @brief Generates the exit status for the minishell based on the provided
/// string argument.
/// Validates that the input string represents a valid numeric value, calculates
/// the exit status,
/// and handles errors such as non-numeric input or values exceeding the maximum
/// allowed.
/// If an error occurs, the function will clean up resources and terminate the
/// program.
/// @param s The string representing the exit status value.
/// @param mo_shell A pointer to the shell structure for managing resources.
/// @return Returns the calculated exit status modulo 256.
static int	exit_gen(char *s, t_mo_shell *mo_shell)
{
	int					i;
	int					sign;
	int					exit_s;
	unsigned long long	result;

	i = 0;
	sign = 1;
	ft_skip_spaces_and_get_sign(s, &i, &sign);
	if (!ft_isnumber(s + i))
	{
		exit_s = ft_err_msg((t_err){2, ERRMSG_NUMERIC_REQUI, s});
		(garbage_collect(mo_shell, 1), exit(exit_s));
	}
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		if (result > __LONG_MAX__)
		{
			exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
			(garbage_collect(mo_shell, 1), exit(exit_s));
		}
		i++;
	}
	return ((result * sign) % 256);
}

/// @brief Handles the `exit` built-in command in the shell.
/// Exits the shell with the specified exit status or the last exit status if
/// none is provided.
/// Validates input arguments and manages errors for non-numeric or excessive
/// arguments.
/// Performs resource cleanup before exiting the program.
/// @param args An array of strings containing the command arguments.
/// The first argument is the command name, and subsequent arguments are the
/// exit status or other inputs.
/// @param mo_shell A pointer to the shell structure for managing resources and
/// state.
/// @param cmd A pointer to the command structure (unused in this function).
/// @return Returns 1 if there are too many arguments; otherwise, the function
/// does not return, as it exits the program.
int	ms_exit(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int	exit_s;

	(void)cmd;
	exit_s = mo_shell->last_exit_status;
	if (args && args[1])
	{
		if (!ft_isnumber(args[1]))
		{
			exit_s = exit_gen(args[1], mo_shell);
		}
		exit_s = (ft_atoi(args[1]) % 256);
	}
	if (args && args[1] && args[2])
	{
		if (args[1] && args[2])
		{
			exit_s = ft_err_msg((t_err){1, ERRMSG_TOO_MANY_ARGS, NULL});
			return (1);
		}
	}
	garbage_collect(mo_shell, 1);
	exit(exit_s);
}
