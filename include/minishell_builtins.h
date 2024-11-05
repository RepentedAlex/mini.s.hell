/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:23:12 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/05 15:46:57 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
# define MINISHELL_BUILTINS_H

# include <stdbool.h>

# include "minishell_types.h"

// == == == BUILTINS == == ==
int			ms_cd(char **args, t_mo_shell *mo_shell);
int			ms_echo(char **args, t_mo_shell *mo_shell);
int			ms_env(char **args, t_mo_shell *mo_shell);
int			ms_exit(char **args, t_mo_shell *mo_shell);
int			ms_export(char **args, t_mo_shell *mo_shell);
int			ms_pwd(char **args, t_mo_shell *mo_shell);
int			ms_unset(char **args, t_mo_shell *mo_shell);

// == == == FONCTIONS SUBSIDIAIRES == == ==
t_builtin	*get_builtin_array(void);
bool		is_builtin(char *str);
int (*launch_builtins(t_cmd	*command))(char **str, t_mo_shell *mo_shell);

#endif
