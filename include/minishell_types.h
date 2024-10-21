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
	INFILE,
	REDIR_O,
	OUTFILE,
	APPEND,
	HEREDOC,
	EOFHD
}			t_lexcat;

// == == == STRUCTURES == == ==

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
	t_lexcat		type;
}			t_token;

typedef struct s_block
{
	char			*str;
	struct s_block	*next;
	struct s_block	*prev;
	t_lexcat		type;
}				t_block;

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
	char	**shell_env;
	int		last_exit_status;
}				t_mo_shell;

typedef struct s_builtin
{
	char	*name;
	int		(*builtin_func)(char **args);
}			t_builtin;

// Structure pour l'Abstract Syntax Tree
typedef struct s_ast_node
{
	int					type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_io_redir
{
	int	in;
	int	out;
	int	err;
}		t_io_redir;

//
// // Structure pour une node de table de commandes
// typedef struct s_command
// {
// 	char			*command;
// 	char			**arguments;
// 	// int				do_background;
// 	t_io_redir		*redir;
// }			t_command;

#endif
