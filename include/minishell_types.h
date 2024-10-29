/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:12:13 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/09 19:12:18 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPES_H
# define MINISHELL_TYPES_H

// == == == LIBRAIRIES == == ==

// Librairies perso

// LEXING
typedef enum e_lexcat
{
	RAW = 0,
	PIPE,
	REDIR_I,
	REDIR_O,
	APPEND,
	HEREDOC,
	EOFHD,
	INFILE,
	OUTFILE,
	CMD
}			t_lexcat;

// == == == STRUCTURES == == ==

typedef struct s_block
{
	char			*str;
	struct s_block	*next;
	struct s_block	*prev;
	t_lexcat		type;
}				t_block;

/// Structure pour les commandes
typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				fd_i;
	int				fd_o;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}		t_cmd;

// Structure mère
/// @brief
/// @param og_input Stocks readline's input.
/// @param expanded_input Stocks to og output with its variable expanded
/// @param splitted_input The splitted og_input
typedef struct s_mo_shell
{
	char	*og_input;
	char	*clean_input;
	char	*expanded_input;
	t_block	*splitted_input;
	t_cmd	*cmds_table;
	char	**shell_env;
	int		last_exit_status;
}				t_mo_shell;

typedef struct s_builtin
{
	char	*name;
	int		(*builtin_func)(char **args);
}			t_builtin;

#endif
