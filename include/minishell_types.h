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
#define MINISHELL_TYPES_H

// == == == STRUCTURES == == ==

// Structure originelle
typedef struct s_shell_env
{
	char	*prompt;
	char	*buffer;
	char	**tokens;
	int		last_exit_status;
}				t_shell_env;

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
