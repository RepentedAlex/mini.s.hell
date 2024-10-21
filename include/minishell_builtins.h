/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:23:12 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/09 19:23:16 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
# define MINISHELL_BUILTINS_H

# include <stdbool.h>

# include "minishell_types.h"

// == == == BUILTINS == == ==
int			ms_cd(char **args);
int			ms_echo(char **args);
int			ms_env(char **args);
int			ms_exit(char **args);
int			ms_export(char **args);
int			ms_pwd(char **args);
int			ms_unset(char **args);

// == == == FONCTIONS SUBSIDIAIRES == == ==
t_builtin	*get_builtin_array(void);
int (*launch_builtins(t_block	*block))(char **);

#endif
