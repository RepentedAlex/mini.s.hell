/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:22:22 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/29 16:14:56 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/// @brief Allocates and sets up the first block in the linked list.
/// This function creates a new `t_block` structure, assigns the `clean_input`
/// from the `mo_shell` struct to the block's string, and initializes other
/// fields.
/// @param mo_shell The shell context containing the input string to assign to
/// the block.
/// @return Returns a pointer to the newly created `t_block` on success, or
/// `NULL` if memory allocation fails or any other error occurs.
t_block	*block_setup_first(t_mo_shell *mo_shell)
{
	t_block	*block;

	block = malloc(sizeof(t_block));
	if (!block)
		return (NULL);
	block->str = ft_strdup(mo_shell->clean_input);
	if (!block->str)
		return (NULL);
	block->next = NULL;
	block->prev = NULL;
	block->type = 0;
	return (block);
}

static t_error	handle_symbol_checks(t_block *nav, int *i)
{
	if (!ft_strncmp(&nav->str[*i], "<<", 2) && handle_hd(nav, i) == \
		ERROR)
		return (ERROR);
	if (!ft_strncmp(&nav->str[*i], ">>", 2) && handle_ap(nav, i))
		return (ERROR);
	if (!ft_strncmp(&nav->str[*i], "<", 1) && handle_ri(nav, i))
		return (NO_ERROR);
	if (!ft_strncmp(&nav->str[*i], ">", 1) && handle_ro(nav, i) == \
		ERROR)
		return (ERROR);
	return (NO_ERROR);
}

t_error	for_space(t_block *nav)
{
	int	i;

	i = 0;
	while (nav->str[i] && !nav->next)
	{
		if (nav->type == RAW && !ft_is_symbol(&nav->str[i]))
		{
			if (handle_no_symbols_no_ifs(nav, &i) == ERROR)
				return (ERROR);
			return (NO_ERROR);
		}
		if (nav->type == RAW && handle_symbol_checks(nav, &i) == ERROR)
			return (ERROR);
		if (nav->type == RAW && !ft_is_ifs(nav->str[i]) && handle_ifs(nav, &i))
			break ;
		if (nav->type == RAW && handle_else(nav, &i))
			continue ;
		i++;
	}
	return (NO_ERROR);
}

//TODO Norm
// t_error	for_space(t_block *nav)
// {
// 	int		i;
//
// 	i = 0;
// 	while (nav->str[i])
// 	{
// 		if (!ft_is_symbol(&nav->str[i]))
// 		{
// 			if (handle_no_symbols_no_ifs(nav, &i) == ERROR)
// 				return (ERROR);
// 			break ;
// 		}
// 		if (!ft_strncmp(&nav->str[i], "<<", 2))
// 		{
// 			if (handle_hd(nav, &i) == ERROR)
// 				return (ERROR);
// 			break ;
// 		}
// 		if (!ft_strncmp(&nav->str[i], ">>", 2))
// 		{
// 			if (handle_ap(nav, &i))
// 				return (ERROR);
// 			break ;
// 		}
// 		if (!ft_strncmp(&nav->str[i], "<", 1) && handle_ri(nav, &i))
// 			break ;
// 		if (!ft_strncmp(&nav->str[i], ">", 1))
// 		{
// 			if (handle_ro(nav, &i) == ERROR)
// 				return (ERROR);
// 			break ;
// 		}
// 		if (!ft_is_ifs(nav->str[i]) && handle_ifs(nav, &i))
// 			break ;
// 		if (handle_else(nav, &i))
// 			continue ;
// 		i++;
// 	}
// 	return (NO_ERROR);
// }

/// @brief Splits the content of the linked list nodes by spaces.
/// This function iterates through the linked list of `t_block` structures,
/// checking if the type is `RAW` and, if so, calling `for_space` to handle
/// the splitting.
/// @param head The head of the linked list to process.
/// @return Returns `NO_ERROR` on success, or `ERROR` if any error occurs
/// during the splitting.
t_error	split_spaces(t_block **head)
{
	t_block	*nav;

	nav = *head;
	if (!nav)
		return (ERROR);
	while (nav)
	{
		if (nav->type == RAW)
			if (for_space(nav) == ERROR)
				return (ERROR);
		nav = nav->next;
	}
	return (NO_ERROR);
}
