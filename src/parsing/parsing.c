/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:58:50 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/21 14:24:26 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_types.h"
#include <libft.h>
#include <stdio.h>
void print_t_blocks(const t_block *blk);

void	clean_empty_nodes(t_block **head)
{
	t_block	*nav;
	t_block	*tmp;

	nav = *head;
	while (nav)
	{
		tmp = nav->next;
		if (nav->str[0] == '\0' || ft_string_is_only_ifs(nav->str))
		{
			if (!nav->prev)
				*head = tmp;
			block_pop(&nav);
		}
		nav = tmp;
	}
}

t_error	lexcat_redir_handler(t_block **head)
{
	if (!head || !*head)
		return (ERROR);
	lexcat_redir_i(head);
	lexcat_redir_o(head);
	return (NO_ERROR);
}

t_error	nodes_unquote_strings(t_block **head)
{
	t_block	*nav;
	char	*tmp;

	nav = *head;
	while (nav)
	{
		if (nav->type != EOFHD)
		{
			tmp = unquote_string(nav->str);
			free(nav->str);
			nav->str = tmp;
		}
		nav = nav->next;
	}
	return (NO_ERROR);
}

#define OFFSET 0
#define QUOTE 1

t_error split_var_space(t_block *nav, t_block **head)
{
	int tb[2];
	char *tmp;
	t_block *insert;

	ft_bzero(tb, sizeof(tb));
	while (nav->str[tb[OFFSET]])
	{
		check_in_quotes(nav->str[tb[OFFSET]], &tb[QUOTE]);
		if (ft_is_ifs(nav->str[tb[OFFSET]++]) && !tb[QUOTE])
		{
			tmp = ft_strndup(nav->str, tb[OFFSET]);
			if (!tmp)
				return (ERROR);
			insert = block_new(tmp);
			tmp = (free(tmp), ft_strdup(nav->str + tb[OFFSET]));
			if (!tmp || !insert)
				return (ERROR);
			(free(nav->str), nav->str = tmp);
			block_add_front(insert, nav);
			if (nav == *head)
				*head = insert;
			tb[OFFSET] = 0;
		}
	}
	return (NO_ERROR);
}

t_error split_blockvar_space(t_block **head)
{
	t_block	*nav;

	nav = *head;
	while (nav)
	{
		if (nav->type != RAW)
		{
			nav = nav->next;
			continue;
		}
		if (split_var_space(nav, head) == ERROR)
			return (ERROR);
		nav = nav->next;
	}
	return (NO_ERROR);
}

#define E_MSG "mini.s.hell: syntax error near unexpected token '|'\n"

t_error	splitter(t_mo_shell *mo_shell)
{
	int		error_ret;
	t_error	sch_ret;

	error_ret = 0;
	if (look_for_pipes(&mo_shell->splitted_input) == true)
	{
		if (check_pipes_syntax(&mo_shell->splitted_input) == ERROR)
			return (printf(E_MSG), mo_shell->last_exit_status = 2, ERROR);
		if (split_pipes(&mo_shell->splitted_input) == ERROR)
			return (mo_shell->last_exit_status = 2, ERROR);
	}
	if (look_for_redir(&mo_shell->splitted_input) == true)
		if (syntax_check_handler(mo_shell, &error_ret, &sch_ret))
			return (sch_ret);
	block_string_tidyer(&mo_shell->splitted_input);
	if (split_spaces(&mo_shell->splitted_input) == ERROR)
		return (mo_shell->last_exit_status = 2, ERROR);
	clean_empty_nodes(&mo_shell->splitted_input);
	if (lexcat_redir_handler(&mo_shell->splitted_input) == ERROR || \
		new_expand_variables(&mo_shell->splitted_input, mo_shell) == ERROR)
		return (ERROR);
	if (split_blockvar_space(&mo_shell->splitted_input) == ERROR)
		return (mo_shell->last_exit_status = 2, ERROR);
	block_string_tidyer(&mo_shell->splitted_input);
	nodes_unquote_strings(&mo_shell->splitted_input);
	return (NO_ERROR);
}

const char *type_to_str(t_lexcat val)
{
	if (val == RAW)
		return ("RAW");
	if (val == PIPE)
		return ("PIPE");
	if (val == REDIR_I)
		return ("REDIR_I");
	if (val == REDIR_O)
		return ("REDIR_O");
	if (val == APPEND)
		return ("APPEND");
	if (val == HEREDOC)
		return ("HEREDOC");
	if (val == EOFHD)
		return ("EOFHD");
	if (val == INFILE)
		return ("INFILE");
	if (val == OUTFILE)
		return ("OUTFILE");
	if (val == CMD)
		return ("CMD");
	return ("UNKOWN");
}

void print_t_blocks(const t_block *blk)
{
	t_block *runner = (t_block *)blk;


	printf("printing t_blocks\n");
	while (runner)
	{
		printf("'%s' of type %s\n", runner->str, type_to_str(runner->type));
		runner = runner->next;
	}
}


t_error	parsing(t_mo_shell *mo_shell)
{
	if (check_open_quotes(mo_shell->og_input) == ERROR)
		return (printf("mini.s.hell: quotes are not closed\n"), ERROR);
	mo_shell->clean_input = string_tidyer(mo_shell->og_input);
	if (mo_shell->clean_input == NULL)
		return (ERROR);
	mo_shell->splitted_input = block_setup_first(mo_shell);
	if (splitter(mo_shell) == ERROR)
		return (ERROR);
	return (NO_ERROR);
}
