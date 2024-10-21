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

// == == == LIBRAIRIES == == ==

// Librairies standard
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

// Libraires persos
# include "minishell_builtins.h"
# include "minishell_types.h"

// == == == MACROS == == ==

// Utile pour t_error.
# define ERROR 1
# define NO_ERROR 0

# define PROMPT "mini.s.hell-> "

// IFS = Internal Fields Separator
// Par défaut <space><tab><newline> sont utilisés pour délimiter chaque token.
# define IFS " \t\n"

// == == == TYPEDEFS == == ==

// t_error permet de faire remonter les erreurs de manière plus lisible.
typedef bool	t_error;

// == == == FONCTIONS == == ==

// mini.s.hell
int		mini_s_hell(int argc, char *argv[], char *envp[], t_mo_shell *mo_shell);

t_error parsing(t_mo_shell *mo_shell);

// parsing
t_error	splitter(t_mo_shell *mo_shell);

int		check_if_var_exists(char *var, char *envp[]);
t_error	check_open_quotes(const char *str);
char	**copy_env(char **envp);
int		count_leading_whitespace(const char *str);
int		count_tokens(const char *str);
void	free_tab(char **array);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	check_in_quotes(char c, int *quotes);
void	garbage_collect(t_mo_shell *data);
void	split_str(char *str, char **ret, int *nb_token, bool *in_word);
void	trim_leading_whitespace(char *str, const int leading_whitespaces);

// blocks
t_error	block_add_after(t_block *ref, t_block *to_insert);
t_error	block_add_back(t_block **head, t_block *node);
t_error	block_add_before(t_block **ref, t_block *to_insert);
t_error	block_add_front(t_block **head, t_block *node);
t_block	*block_goto_last(t_block *head);
t_block	*block_new(char *str);
t_block	*block_setup_first(t_mo_shell *mo_shell);
void	block_string_tidyer(t_block **head);
void	block_split_spaces(t_block *head);

// ft_is
bool	ft_is_alpha(const char c);
bool	ft_is_ifs(char c);
int		ft_is_symbol(const char *str);

// ft_str
t_error	split_spaces(t_block **head);
char	*ft_strchr(const char *s, const int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnjoin(char *src, char *dst, size_t n);
char	*string_tidyer(char *s);
bool	ft_string_is_ifs(char *str);

// pipe inspection
t_error	check_pipes_syntax(t_block **head);
bool	look_for_pipes(t_block **head);
t_error	split_pipes(t_block **head);

// redir inspection
t_error	check_redir_syntax(t_block **head);
bool	look_for_redir(t_block **head);
t_error	split_redir(t_block **head);

// variables expansion
char	*expand_variables(char *src, char *envp[]);

#endif
