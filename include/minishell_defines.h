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
# define SYNTAX_ERR_CODE 2
# define IS_DIR_CODE 126
# define PERM_DENIED_CODE 126
# define CMD_NOT_FOUND_CODE 127
# define NO_SCH_FOD_CODE 127
////////////////////////////////////////////////////////////////////////////////

///ERROR MESSAGES///////////////////////////////////////////////////////////////
# define SYNTAX_ERR_MSG "mini.s.hell: syntax error near unexpected token '%s'\n"
# define IS_DIR_MSG "mini.s.hell: %s is a directory\n"
# define PERM_DENIED_MSG "mini.s.hell: %s: permission denied\n"
# define CMD_NOT_FOUND_MSG "mini.s.hell: %s: command not found\n"
# define NO_SCH_FOD_MSG "mini.s.hell: %s: No such file or directory\n"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////BUILTINS////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///ERROR MESSAGES///////////////////////////////////////////////////////////////
# define UNS_INVALID_ID "mini.s.hell: unset: '%s': not a invalid identifier\n"
////////////////////////////////////////////////////////////////////////////////
///
#endif //MINISHELL_DEFINES_H
