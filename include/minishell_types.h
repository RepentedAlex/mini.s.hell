/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:12:13 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/03 16:06:30 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPES_H
# define MINISHELL_TYPES_H

// == == == LIBRAIRIES == == ==

// Librairies perso

// == == == ENUM == == ==
typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}	t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_err_no;

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

typedef struct s_err
{
	t_err_no	no;
	t_err_msg	msg;
	char		*cause;
}	t_err;

typedef struct s_block
{
	char			*str;
	struct s_block	*next;
	struct s_block	*prev;
	t_lexcat		type;
}				t_block;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	bool			heredoc;
	int				fd_i;
	int				cp_i;
	int				fd_o;
	int				cp_o;
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
	int		(*builtin_func)(char **args, t_mo_shell *mo_shell, t_cmd *cmd);
}			t_builtin;

typedef struct s_pipes
{
	int	pipe[1024][2];
	int	pipe_i;
}		t_pipes;

typedef struct s_pids
{
	int	pid[1024];
	int	pid_i;
}		t_pids;

#endif
