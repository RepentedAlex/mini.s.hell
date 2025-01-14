/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:19:56 by llabonde          #+#    #+#             */
/*   Updated: 2025/01/03 15:56:46 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/// @brief Checks if the given string represents the "-n" option for the echo
/// command.
/// The option is valid if the string starts with '-' and is followed only by
/// 'n' characters.
/// @param str The string to check.
/// @return Returns true if the string is a valid "-n" option, false otherwise.
bool echo_check_option(char *str)
{
	int	i;

	i = 1;
	while (str && str[i] && str[i] == 'n')
	{
		i++;
	}
	if (!str[i])
		return (true);
	return (false);
}

/// @brief Implements the "echo" command in the shell, printing arguments to the
/// standard output.
/// Handles the "-n" option to suppress the trailing newline.
/// @param args Array of arguments passed to the command, with args[0] being
/// "echo".
/// Subsequent elements contain strings to be printed. If "-n" is provided as an
/// argument,
/// the trailing newline will be omitted.
/// @param mo_shell Pointer to the shell structure (unused in this function).
/// @param cmd Pointer to the command structure (unused in this function).
/// @return Returns 0 upon successful execution.
int	ms_echo(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		i;
	bool	option;

	(void)mo_shell;
	(void)cmd;
	i = 1;
	option = false;
	while (args && args[i] && args[i][0] == '-')
	{
		if (echo_check_option(args[i]) == true)
			option = true;
		else
			break ;
		i++;
	}
	while (args && args[i] && args[i][0] != '>')
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	return (0);
}
