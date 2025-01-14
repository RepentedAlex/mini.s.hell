/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:58:50 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/29 18:06:46 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

bool	syntax_check_handler(t_mo_shell *mo_shell, int *error_ret, \
	t_error *value1)
{
	*error_ret = check_redir_syntax(&mo_shell->splitted_input);
	if (*error_ret == 1)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '>'\n"), mo_shell->last_exit_status = 2, true);
	if (*error_ret == 2)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '>>'\n"), mo_shell->last_exit_status = 2, true);
	if (*error_ret == 3)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '<'\n"), mo_shell->last_exit_status = 2, true);
	if (*error_ret == 4)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token '<<'\n"), mo_shell->last_exit_status = 2, true);
	if (*error_ret == 5)
		return (*value1 = printf("mini.s.hell: syntax error near \
unexpected token 'newline'\n"), mo_shell->last_exit_status = 2, true);
	return (false);
}

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

char	*unquote_string(char *str)
{
	int		i;
	int		j;
	int		quotes;
	char	tmp[DEF_BUF_SIZ];
	char	*ret;

	ft_bzero(tmp, DEF_BUF_SIZ);
	quotes = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((quotes == 1 && str[i] == '\'') || (quotes == 2 && str[i] == '\"'))
		{
			check_in_quotes(str[i], &quotes);
			i++;
			continue ;
		}
		check_in_quotes(str[i], &quotes);
		if (!quotes || (quotes == 1 && str[i] != '\'') || (quotes == 2 && str[i] != '\"') || (str[i] != '\'' && str[i] != '"'))
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[i] = '\0';
	ret = ft_strdup(tmp);
	if (!ret)
		return (NULL);
	return (ret);
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

char	*exp_for_hd(char *src)
{
	int		i;
	char	*ret;
	int		quotes;

	ret = str_init();
	quotes = 0;
	i = 0;
	while (src[i])
	{
		check_in_quotes(src[i], &quotes);
		if (quotes != 1 && '$' == src[i])
		{
			i++;
			if (src[i] == '\'' || src[i] == '\"')
			{
				if (src[i] == '\'')
					quotes = 1;
				else
					quotes = 2;
				while (quotes)
				{
					i++;
					if (src[i] == '\'' && quotes == 1)
						quotes = 0;
					else if (src[i] == '\"' && quotes == 2)
						quotes = 0;
				}
				i++;
			}
		}
		else
		{
			ret = append(ret, &src[i], 1);
			i++;
		}
	}
	return (ret);
}

void	new_expand_variables(t_block **head, t_mo_shell *mo_shell)
{
	t_block	*nav;
	char	*tmp;

	nav = *head;
	while (nav)
	{
		if (nav->type != EOFHD)
		{
			tmp = expand_variables(nav->str, mo_shell->shell_env, mo_shell);
			free(nav->str);
			nav->str = tmp;
		}
		nav = nav->next;
	}
}

t_error	splitter(t_mo_shell *mo_shell)
{
	int		error_ret;
	t_error	sch_ret;

	error_ret = 0;
	if (look_for_pipes(&mo_shell->splitted_input) == true)
	{
		if (check_pipes_syntax(&mo_shell->splitted_input) == ERROR)
			return (printf("mini.s.hell: syntax error near unexpected \
token '|'\n"), mo_shell->last_exit_status = 2, ERROR);
		split_pipes(&mo_shell->splitted_input);
	}
	if (look_for_redir(&mo_shell->splitted_input) == true)
		if (syntax_check_handler(mo_shell, &error_ret, &sch_ret))
			return (sch_ret);
	block_string_tidyer(&mo_shell->splitted_input);
	split_spaces(&mo_shell->splitted_input);
	clean_empty_nodes(&mo_shell->splitted_input);
	if (lexcat_redir_handler(&mo_shell->splitted_input) == ERROR) //Surely redundant
		return (ERROR);
	if (check_not_dirfile(&mo_shell->splitted_input, mo_shell) != 0)
		return (ERROR);
	new_expand_variables(&mo_shell->splitted_input, mo_shell);
	nodes_unquote_strings(&mo_shell->splitted_input);
	return (NO_ERROR);
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
