/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:37:25 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/08 18:37:28 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	garbage_collect(t_shell_env *data)
{
	if (data->buffer)
		(free(data->buffer), data->buffer = NULL);
	if (data->tokens)
		(free(data->tokens), data->tokens = NULL);
}