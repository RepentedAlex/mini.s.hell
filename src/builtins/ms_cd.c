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

// static void update_pwd(t_mo_shell *mo_shell, char *new_path,
// t_cmd *cmd, char **args)
// {
// 	char	cwd[DEF_BUF_SIZ];
// 	char	**for_export;

// 	(void)args;
// 	for_export = malloc(sizeof(char *) * 3);
// 	//update_old_pwd(truc);
// 	if (getcwd(cwd, DEF_BUF_SIZ) == NULL)
// 	{
// 		perror(new_path);
// 		return ;
// 	}
// 	for_export[0] = NULL;
// 	for_export[1] = ft_strjoin("PWD=", cwd);
// 	for_export[2] = NULL;
// 	/*	ms_unset(for_export, mo_shell, cmd);
// 	mo_shell->shell_env = add_str_to_array(mo_shell->shell_env, pwd);*/
// 	ms_export(for_export, mo_shell, cmd);
// 	(free(for_export[1]),free(for_export));
// 	free(for_export[1]);
// }

/// @brief Updates the `PWD` environment variable with the new user path and
/// exports it to the environment.
/// @param mo_shell The shell context, used to manage environment variables
/// and state.
/// @param cmd The current command being executed (unused in this function, but
/// included for consistency).
/// @param user_path The new directory path to set as the current working
/// directory.
/// @param export_args An array of arguments for the `export` command, used to
/// update the environment with the new `PWD` value.
static void	update_var(t_mo_shell *mo_shell, t_cmd *cmd, char *user_path, \
						char *export_args[3])
{
	char	*new_pwd;

	new_pwd = append(ft_strdup("PWD="), user_path, ft_strlen(user_path));
	export_args[0] = "lol";
	export_args[1] = new_pwd;
	export_args[2] = NULL;
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
	char	*export_args[3];
	char	*home_dir;

	if (!mo_shell->shell_env)
		return (ft_putstr_fd("No environment\n", 1), 0);
	user_path = NULL;
	if (find_var("HOME", mo_shell->shell_env) == -1)
		return (ft_putstr_fd("mini.s.hell: cd: HOME not set\n", 1), 0);
	home_dir = get_var_content("HOME", mo_shell->shell_env);
	user_path = append(user_path, home_dir, ft_strlen(home_dir));
	free(home_dir);
	if (!user_path)
		return (-1);
	if (chdir(user_path) == 0)
		update_var(mo_shell, cmd, user_path, export_args);
	else
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
	char	*new_pwd;
	char	*tmp;
	char	*export_args[3];
	int		res;

	tmp = NULL;
	res = chdir(path);
	tmp = getcwd(NULL, 0);
	if (res == -1 || tmp == NULL)
		return (ft_putstr_fd("Couldn't change directory\n", 2), 1);
	new_pwd = NULL;
	if (res != 0)
	{
		printf("mini.s.hell: %s: Invalid argument\n", path);
		return (-res);
	}
	new_pwd = append(new_pwd, "PWD=", ft_strlen("PWD="));
	new_pwd = append(new_pwd, tmp, ft_strlen(tmp));
	free(tmp);
	export_args[0] = "lol";
	export_args[1] = new_pwd;
	export_args[2] = NULL;
	ms_export(export_args, mo_shell, cmd);
	free(new_pwd);
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
	if (args[1] && args[2])
		return (ft_putstr_fd("mini.s.hell: cd: invalid arguments\n", 2), \
			0);
	if (!args[1])
		return (cd_to_home(mo_shell, cmd));
	return (cd_to_path(args[1], mo_shell, cmd));
}
