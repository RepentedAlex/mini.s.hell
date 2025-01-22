/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:37:10 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 22:37:11 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

char	*str_init(void)
{
	char	*ret;

	ret = malloc(sizeof(char));
	if (!ret)
		return (NULL);
	*ret = '\0';
	return (ret);
}

void	init_les(char **les, size_t *les_len, t_mo_shell *mo_shell)
{
	*les = ft_itoa(mo_shell->les);
	if (!*les)
		*les = 0;
	*les_len = ft_strlen(*les);
}
