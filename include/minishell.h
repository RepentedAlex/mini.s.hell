/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:49:16 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/08 11:50:04 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// == INCLUDES STD ==
# include <curses.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

//	== MACROS ==
// Utile pour t_error.
# define ERROR 1
# define NO_ERROR 0

# define PROMPT "minishell-> "

// IFS = Internal Fields Separator
// Par défaut <space><tab><newline> sont utilisés pour délimiter chaque token.
# define IFS " \t\n"

//	== TYPEDEFS ==
// t_error permet de faire remonter les erreurs de manière plus lisible.
typedef bool	t_error;

//	== STRUCTURES ==

// Structure originelle
typedef struct s_shell_env
{
	char	*prompt;
	char	*buffer;
	int		last_exit_status;
}				t_shell_env;

// Structure pour l'Abstract Syntax Tree
typedef struct s_ast_node
{
	int					type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

// Structure pour une node de table de commandes
typedef struct s_simple_command
{
	char	*command;
	char	*option;
	char	**arguments;
	int		do_background;
}			t_simple_command;

typedef struct s_io_redir
{
	int	in;
	int	out;
	int	err;
}		t_io_redir;

// Structure pour la table de commandes
typedef struct s_command_table
{
	t_simple_command	*table;
	t_io_redir			*redir;
}						t_command_table;

#endif
