/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:12:18 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/21 15:12:20 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*type_to_str(t_lexcat val)
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

void	print_t_blocks(const t_block *blk)
{
	t_block	*runner;

	runner = blk;
	printf("printing t_blocks\n");
	while (runner)
	{
		printf("'%s' of type %s\n", runner->str, type_to_str(runner->type));
		runner = runner->next;
	}
}
