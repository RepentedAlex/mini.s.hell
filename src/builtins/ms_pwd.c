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

/// @brief Prints the current working dir as per the PWD variable in the shell
/// environment.
/// @param args
/// @param cmd
/// @return
int	ms_pwd(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		var_index;
	char	*var_content;
	char	*cwd;
	char	*tmp;

	(void)cmd;
	(void)args;
	cwd = NULL;
	tmp = NULL;
	if (getcwd(cwd, DEF_BUF_SIZ) == NULL)
		return (free(cwd), ft_putstr_fd(\
"mini.s.hell: error retrieving current directory\n", STDERR_FILENO), 1);
	cwd = ft_strdup("PWD=");
	cwd = append(cwd, tmp, DEF_BUF_SIZ);
	(free(tmp), tmp = NULL);
	var_index = var_exst("PWD", mo_shell->shell_env);
	if (var_index == -1)
		return (write(1, "\n", 1), 1);
	var_content = mo_shell->shell_env[var_index];
	while (*var_content != '=')
		var_content++;
	var_content++;
	write(1, var_content, ft_strlen(var_content));
	return (free(cwd), cwd = NULL, write(1, "\n", 1), 0);
}
