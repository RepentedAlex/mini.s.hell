/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:24:40 by llabonde          #+#    #+#             */
/*   Updated: 2024/12/10 16:11:58 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtins.h"
#include <libft.h>

static void	update_pwd(t_mo_shell *mo_shell, t_cmd *cmd)
{
	char	*tmp;
	char	*path_tmp;
	char	*new_pwd;
	char	*export_args[3];

	export_args[0] = "lol";
	export_args[2] = NULL;
	new_pwd = ft_strdup("PWD=");
	path_tmp = get_var_content("PWD", mo_shell->shell_env);
	tmp = append(ft_strdup("OLDPWD="), path_tmp, ft_strlen(path_tmp));
	free(path_tmp);
	export_args[1] = tmp;
	ms_export(export_args, mo_shell, cmd);
	free(tmp);
	export_args[1] = NULL;
	tmp = getcwd(NULL, 0);
	new_pwd = append(new_pwd, tmp, ft_strlen(tmp));
	free(tmp);
	export_args[1] = new_pwd;
	ms_export(export_args, mo_shell, cmd);
	free(new_pwd);
}

/// @brief Changes the current directory to the user's home directory as
/// specified by the `HOME` environment variable.
/// @param mo_shell The shell context, used to manage environment variables and
/// state.
/// @param cmd The current command being executed (unused in this function, but
/// included for consistency).
/// @return Returns 0 on success. Returns -1 if the `HOME` environment variable
/// is not set, or if changing the directory fails.
/// If the `HOME` variable is not found or an error occurs, an appropriate error
/// message is printed.
static int	cd_to_home(t_mo_shell *mo_shell, t_cmd *cmd)
{
	char	*user_path;
	char	*home_dir;

	(void)cmd;
	user_path = NULL;
	if (find_var("HOME", mo_shell->shell_env) == -1)
		return (err_msg(CD_NO_HOME_MSG, NULL), 0);
	home_dir = get_var_content("HOME", mo_shell->shell_env);
	user_path = append(user_path, home_dir, ft_strlen(home_dir));
	free(home_dir);
	if (!user_path)
		return (-1);
	if (chdir(user_path) != 0)
		return (free(user_path), -1);
	free(user_path);
	return (0);
}

/// @brief Changes the current directory to the specified path and updates the
/// `PWD` environment variable.
/// @param path The path to change to. This can be an absolute or relative
/// directory path.
/// @param mo_shell The shell context, used to manage environment variables and
/// state.
/// @param cmd The current command being executed (unused in this function, but
/// included for consistency).
/// @return Returns 0 on success. Returns 1 if the directory change fails, and
/// prints an error message.
/// If an invalid argument is passed to `chdir`, a specific error message is
/// printed.
static int	cd_to_path(char *path, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		res;

	(void)cmd;
	(void)mo_shell;
	res = chdir(path);
	if (res == -1)
		return (ft_putstr_fd("Couldn't change directory\n", 2), 1);
	if (res != 0)
	{
		printf("mini.s.hell: %s: Invalid argument\n", path);
		return (-res);
	}
	return (0);
}

/// @brief Changes the current working directory.
/// @param args The arguments passed to the `cd` command. `args[1]` is the
/// target directory or path.
/// @param mo_shell The shell context, used to manage environment variables and
/// state.
/// @param cmd The current command being executed (unused in this function, but
/// included for consistency).
/// @return Returns 0 on success. If the arguments are invalid or the directory
/// change fails, an error message is printed.
int	ms_cd(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (args[1] && args[2])
		return (ft_putstr_fd("mini.s.hell: cd: invalid arguments\n", 2), \
			0);
	if (!args[1])
		exit_status = cd_to_home(mo_shell, cmd);
	else
		cd_to_path(args[1], mo_shell, cmd);
	update_pwd(mo_shell, cmd);
	return (exit_status);
}
