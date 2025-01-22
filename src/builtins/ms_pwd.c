/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:53:08 by apetitco          #+#    #+#             */
/*   Updated: 2024/12/10 16:17:53 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/// @brief Handles the `pwd` built-in command, which prints the current working
/// directory.
/// @param args Command-line arguments passed to the `pwd` command. If an
/// invalid option is passed (e.g., an argument starting with '-'), an error
/// message is displayed, and the function exits with a non-zero status.
/// @param mo_shell Pointer to the shell structure containing the shell's state,
/// including environment variables and the last exit status.
/// @param cmd Pointer to the command structure (not used in this function,
/// provided for consistency with other built-in functions).
/// @return Returns 0 on success. Returns 2 if an invalid option is passed.
/// Returns 1 if there is an error retrieving the current working directory.
int	ms_pwd(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = NULL;
	if (args && args[1] && args[1][0] == '-')
		return (write(1, "Invalid option\n", 15), \
			mo_shell->les = 2, 2);
	cwd = getcwd(cwd, DEF_BUF_SIZ);
	if (cwd == NULL)
		return (free(cwd), err_msg(PWD_RET_CWD_MSG, NULL), 1);
	write(1, cwd, ft_strlen(cwd));
	return (free(cwd), write(1, "\n", 1), 0);
}
