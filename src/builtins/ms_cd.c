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

static int	cd_to_home(t_mo_shell *mo_shell, t_cmd *cmd)
{
	char	*user_path;
	char	*new_pwd;
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
	{
		new_pwd = append(ft_strdup("PWD="), user_path, \
			ft_strlen(user_path));
		export_args[0] = "lol";
		export_args[1] = new_pwd;
		export_args[2] = NULL;
		ms_export(export_args, mo_shell, cmd);
		free(new_pwd);
	}
	else
		return (free(user_path), -1);
	free(user_path);
	return (0);
}

static int	cd_to_path(char *path, t_mo_shell *mo_shell, t_cmd *cmd)
{
	char	*new_pwd;
	char	*export_args[3];
	int		res;

	new_pwd = getcwd(NULL, DEF_BUF_SIZ);
	if (!new_pwd)
		return (perror("mini.s.hell: cd "), 1);
	res = chdir(path);
	if (res != 0)
	{
		printf("mini.s.hell: %s: No such file or directory\n", path);
		return (free(new_pwd), -res);
	}
	if (var_exst("PWD", mo_shell->shell_env) != -1)
	{
		export_args[0] = "lol";
		export_args[1] = append(ft_strdup("PWD="), new_pwd, \
			ft_strlen(new_pwd));
		export_args[2] = NULL;
		ms_export(export_args, mo_shell, cmd);
		(free(new_pwd), free(export_args[1]));
	}
	return (0);
}

/// @brief
/// @param args
/// @param cmd
/// @return
int	ms_cd(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	if (args[1] && args[2])
		return (ft_putstr_fd("mini.s.hell: cd: invalid arguments\n", 2), \
			0);
	if (!args[1])
		return (cd_to_home(mo_shell, cmd));
	return (cd_to_path(args[1], mo_shell, cmd));
}
