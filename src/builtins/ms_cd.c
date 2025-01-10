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

// static void update_pwd(t_mo_shell *mo_shell, char *new_path, t_cmd *cmd, char **args)
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

/// @brief
/// @param args
/// @param cmd
/// @return
int	ms_cd(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	char	*user;
	char	*user_path;
	char	*new_pwd;
	char	*export_args[3];

	user_path = ft_strdup("/home/");
	new_pwd = NULL;
	if (!user_path)
		return (-1);
	user = getenv("USER");
	user_path = append(user_path, user, ft_strlen(user));
	int	res;
	if (args[1] && args[2])
		return (ft_putstr_fd("mini.s.hell: cd: invalid argument.s\n", 2), 0);
	if (!args[1])
	{
		res = chdir(user_path);
		if (res == 0)
		{
			new_pwd = ft_strdup("PWD=");
			new_pwd = append(new_pwd, user_path, ft_strlen(user_path));
			export_args[0] = "lol";
			export_args[1] = new_pwd;
			export_args[2] = NULL;
			ms_export(export_args, mo_shell, cmd);
		}
		else
			return (-res);
	}
	else
	{
		if (getcwd(new_pwd, DEF_BUF_SIZ) == NULL)
			return (perror("mini.s.hell: cd "), 1);
		(free(new_pwd), new_pwd = NULL);
		res = chdir(args[1]);
		if (res == 0 && var_exst("PWD", mo_shell->shell_env) == -1)
			return (res);
		else if (res == 0)
		{
			new_pwd = getcwd(new_pwd, DEF_BUF_SIZ);
			export_args[0] = "lol";
			export_args[1] = append(ft_strdup("PWD="), new_pwd, ft_strlen(new_pwd));
			export_args[2] = NULL;
			ms_export(export_args, mo_shell, cmd);
		}
		else
			printf("mini.s.hell: %s: No such file or directory\n", args[1]);
		return (-res);
	}
	return (0);
}
