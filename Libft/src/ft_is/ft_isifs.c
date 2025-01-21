/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_ifs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:34:27 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/21 21:34:30 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define IFS " \t\n"

bool	ft_is_ifs(const char c)
{
	int	i;

	i = -1;
	while (IFS[++i])
		if (IFS[i] == c)
			return (true);
	return (false);
}
