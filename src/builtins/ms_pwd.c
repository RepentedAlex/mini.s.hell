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

t_error	no_var_in_env(t_mo_shell *mo_shell, char *cwd, char *created_wd)
{
	printf("%s\n", &cwd[4]);
	created_wd = NULL;
	created_wd = append(created_wd, cwd, ft_strlen(cwd));
	free(cwd);
	if (add_str_to_array(&mo_shell->shell_env, created_wd) == ERROR)
		return (ERROR);
	return (NO_ERROR);
}

t_error	retrieve_cwd(char *cwd, char **tmp)
{
	*tmp = getcwd(cwd, DEF_BUF_SIZ);
	if (*tmp == NULL)
	{
		free(*tmp);
		ft_putstr_fd("mini.s.hell: error retrieving current directory\n", \
			STDERR_FILENO);
		return (ERROR);
	}
	return (NO_ERROR);
}

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
	char	*created_wd;

	((void)cmd, created_wd = NULL);
	cwd = NULL;
	if (args && args[1] && args[1][0] == '-')
		return (write(1, "Invalid option\n", 15), \
			mo_shell->last_exit_status = 2, 2);
	if (retrieve_cwd(cwd, &tmp) == ERROR)
		return (1);
	cwd = ft_strdup("PWD=");
	cwd = append(cwd, tmp, DEF_BUF_SIZ);
	(free(tmp), tmp = NULL);
	var_index = var_exst("PWD", mo_shell->shell_env);
	if (var_index == -1)
		return (no_var_in_env(mo_shell, cwd, created_wd));
	var_content = mo_shell->shell_env[var_index];
	while (*var_content != '=')
		var_content++;
	var_content++;
	write(1, var_content, ft_strlen(var_content));
	return (free(cwd), cwd = NULL, write(1, "\n", 1), 0);
}
