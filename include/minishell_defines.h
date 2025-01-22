/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_defines.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:21:53 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/21 11:22:42 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINES_H
# define MINISHELL_DEFINES_H

# define MINISHELL_VERSION_MAJOR 1

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////MAIN//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///ERROR CODES//////////////////////////////////////////////////////////////////
# define STX_ERR_CODE 2
# define IS_DIR_CODE 126
# define PERM_DENIED_CODE 126
# define CMD_NOT_FOUND_CODE 127
# define NO_SCH_FOD_CODE 127
////////////////////////////////////////////////////////////////////////////////

///ERROR MESSAGES///////////////////////////////////////////////////////////////
# define PIP_STX_MSG "mini.s.hell: syntax error near unexpected token `|'\n"
# define APP_STX_MSG "mini.s.hell: syntax error near unexpected token '>>'\n"
# define HD_STX_MSG "mini.s.hell: syntax error near unexpected token '<<'\n"
# define NEW_STX_MSG "mini.s.hell: syntax error near unexpected token 'newline'\
	\n"
# define REI_STX_MSG "mini.s.hell: syntax error near unexpected token '<'\n"
# define REO_STX_MSG "mini.s.hell: syntax error near unexpected token '>'\n"
# define IS_DIR_MSG "mini.s.hell: %s is a directory\n"
# define PERM_DENIED_MSG "mini.s.hell: %s: permission denied\n"
# define CMD_NOT_FOUND_MSG "mini.s.hell: %s: command not found\n"
# define NO_SCH_FOD_MSG "mini.s.hell: %s: No such file or directory\n"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////BUILTINS////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///ERROR CODES//////////////////////////////////////////////////////////////////
# define CD_NO_HOME_CODE 1
# define CD_NO_SCH_FOD_CODE 1
# define EXP_INV_ID_CODE 1
# define EXP_INV_OPT_CODE 2
////////////////////////////////////////////////////////////////////////////////

///ERROR MESSAGES///////////////////////////////////////////////////////////////
# define CD_NO_HOME_MSG "mini.s.hell: cd: HOME not set"
# define CD_NO_SCH_FOD_MSG "mini.s.hell: cd: %s: No such file or directory\n"
# define EXP_INV_ID_MSG "mini.s.hell: export: `%s': not a valid identifier\n"
# define EXP_INV_OPT_MSG "mini.s.hell: export: %s: invalid option\n"
# define PWD_RET_CWD_MSG "mini.s.hell: pwd: couldn't retrieving current \
	directory\n"
# define UNS_INV_ID_MSG "mini.s.hell: unset: `%s': not a invalid identifier\n"
////////////////////////////////////////////////////////////////////////////////
///
#endif //MINISHELL_DEFINES_H
