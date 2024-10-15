/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:22:22 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/15 13:22:25 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_block *block_setup_first(t_mo_shell *mo_shell)
{
	t_block *block;

	block = malloc(sizeof(t_block));
	if (!block)
		return (NULL);
	block->str = strdup(mo_shell->expanded_input);	//TODO ft_strdup
	if (!block->str)
		return (NULL);
	block->next = NULL;
	block->prev = NULL;
	block->type = 0;
	free(mo_shell->expanded_input);
	mo_shell->expanded_input = NULL;
	return (block);
}
