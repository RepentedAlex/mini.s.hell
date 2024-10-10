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
#include "minishell_builtins.h"
#include "minishell_lexing.h"
#include "minishell_types.h"

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
int		mini_s_hell(int argc, char *argv[], char *envp[]);

t_error	check_quotes(const char *str);
int		count_leading_whitespace(const char *str);
int		count_tokens(const char *str);
bool	is_ifs(char c);
void	free_tab(char **array);
int		strcmp(const char *s1, const char *s2);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *str);
void	garbage_collect(t_shell_env *data);
void	split_str(char *str, char **ret, int *nb_token, bool *in_word);
void	trim_leading_whitespace(char *str, const int leading_whitespaces);

#endif
