/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:49:16 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/26 17:15:52 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// == == == LIBRAIRIES == == ==

// Librairies standard
# include <curses.h>
# include <dirent.h>
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

extern pid_t	g_signal_pid;

// == == == MACROS == == ==

// Utile pour t_error.
# define ERROR 1
# define NO_ERROR 0

# define PROMPT "mini.s.hell-> "

// IFS = Internal Fields Separator
// Par défaut <space><tab><newline> sont utilisés pour délimiter chaque token.
# define IFS " \t\n"

# define DEF_BUF_SIZ 1024

// == == == TYPEDEFS == == ==

// t_error permet de faire remonter les erreurs de manière plus lisible.
typedef bool	t_error;

// == == == FONCTIONS == == ==

// mini.s.hell
int		mini_s_hell(int argc, char *argv[], char *envp[], t_mo_shell *mo_shell);

t_error	parsing(t_mo_shell *mo_shell);

// parsing
t_error	splitter(t_mo_shell *mo_shell);

int		var_exst(char *var, char *envp[]);
char	*var_expander(char *ret, char *src, int *i, char *envp[]);

int check_not_dirfile(t_block **head, t_mo_shell *mo_shell);

int check_if_dirfile_exist(char *path, t_mo_shell *mo_shell);
t_error	check_open_quotes(const char *str);
char	**copy_env(char **envp);
int		count_leading_whitespace(const char *str);
int		count_tokens(const char *str);
int		find_var(char *src, char *envp[]);
void	free_2d_tab(char **array);
void	free_tab(char **array);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*get_pwd(char	**envp);
void	check_in_quotes(char c, int *quotes);
void	garbage_collect(t_mo_shell *data, int mode);
void	splash_screen(void);
void	split_str(char *str, char **ret, int *nb_token, bool *in_word);
void	trim_leading_whitespace(char *str, const int leading_whitespaces);
char	*str_init(void);

// blocks
t_error	block_add_after(t_block *ref, t_block *to_insert);
t_error	block_add_back(t_block **head, t_block *node);
t_error	block_add_before(t_block *ref, t_block *to_insert);
t_error	block_add_front(t_block **head, t_block *node);
t_block	*block_goto_last(t_block *head);
t_block	*block_new(char *str);
void	block_pop(t_block **block);
t_block	*block_setup_first(t_mo_shell *mo_shell);
void	block_string_tidyer(t_block **head);
void	block_split_spaces(t_block *head);

//builtins
int		ft_err_msg(t_err err);

// cmd
t_cmd	*cmd_new(char *str);
t_cmd	*cmd_goto_last(t_cmd *head);
t_error	cmd_add_after(t_cmd *ref, t_cmd *to_insert);
t_error	cmd_add_back(t_cmd *head, t_cmd *node);

// execution
t_error	execution(t_mo_shell *mo_shell);
void	execute_cl(t_mo_shell *mo_shell);
char	*get_path(char *cmd, char *envp[]);
void	setup_redirs(t_cmd *to_launch, t_pipes *pipes, int mode);

t_error fill_cmd_and_args(t_cmd **cmd_head, t_block **block_head);
t_error	open_redir_files(t_cmd **cmd_head, t_block **block_head, t_mo_shell *mo_shell);
t_error	open_redir_i(t_cmd **cmd_head, t_block **block_head, t_mo_shell *mo_shell);
t_error	open_redir_o(t_cmd **cmd_head, t_block **block_head);
t_error	pipeline_setup(t_mo_shell *mo_shell);
void	setup_pipes(t_cmd **cmd_head);
t_cmd	*spltd_in_to_cmd_blocks(t_block **head);

// exit
void	close_fds(t_cmd **head);

// file descriptors
t_error	open_file_out(t_block *nav_block, t_cmd *nav_cmd, int mode);
t_error	open_file_in(t_block *nav_block, t_cmd *nav_cmd, int mode, t_mo_shell *mo_shell);

// ft_is
bool	ft_is_alpha(const char c);
bool	ft_is_ifs(char c);
int		ft_is_symbol(const char *str);

char	*append(char *dest, char *src, size_t n);
t_error	split_spaces(t_block **head);
char	*ft_strnjoin(char *src, char *dst, size_t n);
char	*string_tidyer(char *s);
char	*unquote_string(char *str);
bool	ft_string_is_ifs(char *str);

// heredocs
bool	check_if_word_is_quoted(const char *word);
char	*remove_quotes(char *str);

// pipe inspection
t_error	check_pipes_syntax(t_block **head);
bool	look_for_pipes(t_block **head);
t_error	split_pipes(t_block **head);

// redir inspection
int		check_after_redir(char *str, int i);
int		check_redir_syntax(t_block **head);
bool	check_dou_redir(int *i, t_block *nav, int *value1);
bool	check_sing_redir(int *i, t_block *nav, int *value1);
bool	look_for_redir(t_block **head);
t_error	lexcat_redir_handler(t_block **head);
t_error	lexcat_redir_i(t_block **head);
t_error	lexcat_redir_o(t_block **head);

//Signals
void	signals(void);

// splitters
t_error handle_ap(t_block *nav, int *i);
int		handle_else(t_block *nav, int *i);

t_error handle_hd(t_block *nav, int *i);
int		handle_ifs(t_block *nav, int *i);
int		handle_quotes(t_block *nav, int *i);
int		handle_ri(t_block *nav, int *i);

t_error handle_ro(t_block *nav, int *i);
int		handle_no_symbols_no_ifs(t_block *nav, int *i);

// utilitaries
t_error add_str_to_array(char ***array, char *str);
bool	ft_string_is_only_ifs(char *str);

// variables expansion
char	*expand_variables(char *src, char *envp[], t_mo_shell *mo_shell);
char	*get_var_content(char *var_name, char **env);

#endif
