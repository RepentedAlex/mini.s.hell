/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:24:40 by llabonde          #+#    #+#             */
/*   Updated: 2024/11/20 18:02:32 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtins.h"
#include <libft.h>

static void update_pwd(t_mo_shell *mo_shell, char *new_path, t_cmd *cmd, char **args)
{
	char	cwd[1024];
	char	*pwd;
	char	**for_unset;

	(void)args;
	for_unset = malloc(sizeof(char *) * 3);
	for_unset[0] = NULL;
	for_unset[1] = ft_strdup("PWD");
	for_unset[2] = NULL;
	//update_old_pwd(truc);
	if (getcwd(cwd, 1024) == NULL)
	{
		perror(new_path);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return ;
	ms_unset(for_unset, mo_shell, cmd);
	mo_shell->shell_env = add_str_to_array(mo_shell->shell_env, pwd);
	(free(for_unset[1]),free(for_unset));
	free(pwd);
}

/// @brief
/// @param args
/// @param cmd
/// @return
int	ms_cd(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	(void)cmd;
	int	res;
	if (!args[1] || args[2])
		return (ft_putstr_fd("mini.s.hell: cd: missing or invalid argument.s\n", 2), 0);
	else
	{
		res = chdir(args[1]);
		if (res == 0)
			update_pwd(mo_shell, args[1], cmd, &args[1]);
		else
			return (res);
	}
	return (0);
}
