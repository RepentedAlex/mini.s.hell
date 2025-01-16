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

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////MACROS/////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Utile pour t_error.
# define ERROR 1
# define NO_ERROR 0

# define PROMPT "mini.s.hell-> "

// IFS = Internal Fields Separator
// Par défaut <space><tab><newline> sont utilisés pour délimiter chaque token.
# define IFS " \t\n"

# define DEF_BUF_SIZ 1024

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////TYPEDEFS////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// t_error permet de faire remonter les erreurs de manière plus lisible.
typedef bool	t_error;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////FUNCTIONS////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///MAIN BLOCKS//////////////////////////////////////////////////////////////////
t_error	execution(t_mo_shell *mo_shell);
int		mini_s_hell(int argc, char *argv[], char *envp[], t_mo_shell *mo_shell);
t_error	parsing(t_mo_shell *mo_shell);
void	signals(void);
t_error	splitter(t_mo_shell *mo_shell);
////////////////////////////////////////////////////////////////////////////////

///CHECKERS/////////////////////////////////////////////////////////////////////
int		check_after_redir(char *str, int i);
int		check_if_dirfile_exist(char *path, t_mo_shell *mo_shell);
bool	check_if_word_is_quoted(const char *word);
void	check_in_quotes(char c, int *quotes);
int		check_input(t_mo_shell *mo_shell);
int		check_not_dirfile(t_block **head, t_mo_shell *mo_shell);
t_error	check_open_quotes(const char *str);
t_error	check_pipes_syntax(t_block **head);
int		check_redir_syntax(t_block **head);
bool	ft_is_ifs(char c);
int		ft_is_symbol(const char *str);
bool	ft_string_is_only_ifs(char *str);
bool	is_valid_variable_name(char *vr_name);
bool	syntax_check_handler(t_mo_shell *mo_shell, int *error_ret, \
	t_error *value1);
bool	words_in_str(char *str);
////////////////////////////////////////////////////////////////////////////////

///CLOSERS//////////////////////////////////////////////////////////////////////
void	close_pipes(t_pipes *pipes);
t_error	wait_for_processes(t_pids *pids_array);
////////////////////////////////////////////////////////////////////////////////

///GENERATORS///////////////////////////////////////////////////////////////////
int		gen_number(char *num, char **filename);
////////////////////////////////////////////////////////////////////////////////

///GETTERS//////////////////////////////////////////////////////////////////////
char	*get_path(char *cmd, char *envp[]);
char	*get_var_content(char *var_name, char **env);
////////////////////////////////////////////////////////////////////////////////

///INITIALISERS/////////////////////////////////////////////////////////////////
void	init_cmd_args_fill(t_mo_shell *mo_shell, t_block **nav_block, \
	t_cmd **nav_cmd, bool *block_has_cmd);
t_cmd	*init_exec_seq(t_mo_shell *mo_shell, t_pipes *pipes, t_pids *pids);
void	init_les(char **les, size_t *les_len, t_mo_shell *mo_shell);
t_error	init_min_env(t_mo_shell *mo_shell);
t_error	init_shell(void);
t_block	*init_spl_to_cmdb(t_cmd **ret, t_cmd **tmp, int *number_of_cmds, \
	t_block **head);
char	*str_init(void);
////////////////////////////////////////////////////////////////////////////////

///MODIFYERS////////////////////////////////////////////////////////////////////
t_error	expand_cmd_path(t_cmd **head, char *envp[]);
void	expand_hd_i(int fd, t_mo_shell *mo_shell, char *line, \
	char **expdd_line);
t_error	new_expand_variables(t_block **head, t_mo_shell *mo_shell);
char	*unquote_delimiter(char *str);
////////////////////////////////////////////////////////////////////////////////

///TO SORT//////////////////////////////////////////////////////////////////////
int		var_exst(char *var, char *envp[]);
char	*var_expander(char *ret, char *src, int *i, char *envp[]);
char	**copy_env(char **envp);
int		find_var(char *src, char *envp[]);
void	free_2d_tab(char **array);
void	garbage_collect(t_mo_shell *data, int mode);
void	splash_screen(void);
// blocks
t_error	block_add_after(t_block *ref, t_block *to_insert);
t_error	block_add_back(t_block **head, t_block *node);
t_block	*block_goto_last(t_block *head);
t_block	*block_new(char *str);
void	block_pop(t_block **block);
t_block	*block_setup_first(t_mo_shell *mo_shell);
void	block_string_tidyer(t_block **head);
//builtins
int		ft_err_msg(t_err err);
// cmd
t_cmd	*cmd_new(char *str);
t_cmd	*cmd_goto_last(t_cmd *head);
t_error	cmd_add_after(t_cmd *ref, t_cmd *to_insert);
t_error	cmd_add_back(t_cmd *head, t_cmd *node);
// execution
t_error	fill_cmd_and_args(t_mo_shell *mo_shell);
int		fork_for_cmd(t_mo_shell *mo_shell, t_cmd *to_launch, \
	t_pipes *pipes_array, t_pids *pids_array);
t_error	open_redir_files(t_cmd **cmd_head, t_block **block_head, t_mo_shell \
	*mo_shell);
t_error	open_redir_i(t_cmd **cmd_head, t_block **block_head, t_mo_shell \
	*mo_shell);
t_error	open_redir_o(t_cmd **cmd_head, t_block **block_head);
t_error	pipeline_setup(t_mo_shell *mo_shell);
void	setup_pipes(t_cmd **cmd_head);
t_cmd	*spltd_in_to_cmd_blocks(t_block **head);
// exit
void	close_fds(t_cmd **head);
// file descriptors
t_error	open_file_out(t_block *nav_block, t_cmd *nav_cmd, int mode);
t_error	open_file_in(t_block *nav_block, t_cmd *nav_cmd, int mode, t_mo_shell \
	*mo_shell);
char	*append(char *dest, char *src, size_t n);
t_error	split_spaces(t_block **head);
char	*ft_strnjoin(char *src, char *dst, size_t n);
char	*string_tidyer(char *s);
char	*unquote_string(char *str);
bool	ft_string_is_ifs(char *str);
// heredocs
void	heredoc_filler(char *delimiter, int fd, t_mo_shell *mo_shell);
char	*remove_quotes(char *str);
void	heredoc_handler(t_block *nav_block, t_cmd *nav_cmd, t_mo_shell \
	*mo_shell);
// pipe inspection
bool	look_for_pipes(t_block **head);
t_error	split_pipes(t_block **head);
// redir inspection
bool	look_for_redir(t_block **head);
t_error	lexcat_redir_handler(t_block **head);
t_error	lexcat_redir_i(t_block **head);
t_error	lexcat_redir_o(t_block **head);
// splitters
t_error	handle_ap(t_block *nav, int *i);
int		handle_else(t_block *nav, int *i);
t_error	handle_hd(t_block *nav, int *i);
int		handle_ifs(t_block *nav, int *i);
int		handle_quotes(t_block *nav, int *i);
int		handle_ri(t_block *nav, int *i);
t_error	handle_ro(t_block *nav, int *i);
int		handle_no_symbols_no_ifs(t_block *nav, int *i);
// utilitaries
t_error	add_str_to_ra(char ***array, char *str);
// variables expansion
char	*expand_variables(char *src, t_mo_shell *mo_shell);
void	hdus_handle_dollar(char *str, char *tmp, int *i, int *j);
////////////////////////////////////////////////////////////////////////////////

#endif
