/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_insert_before.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:02:15 by bgoulard          #+#    #+#             */
/*   Updated: 2025/01/20 17:04:22 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell_types.h"

void	block_add_front(t_block *insert, t_block *list)
{
	insert->prev = list->prev;
	insert->next = list;
	if (list->prev)
		list->prev->next = insert;
	list->prev = insert;
}
