/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifyers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:56:07 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 14:56:31 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

char	*hd_unquote_string(char *str)
{
	int		i;
	int		j;
	char	tmp[DEF_BUF_SIZ];
	char	*ret;

	ft_bzero(tmp, DEF_BUF_SIZ);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			hdus_handle_dollar(str, tmp, &i, &j);
		if (str[i] != '\'' && str[i] != '"')
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

char	*unquote_delimiter(char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = hd_unquote_string(str);
	return (tmp);
}

void	expand_hd_i(int fd, t_mo_shell *mo_shell, char *line, char **expdd_line)
{
	*expdd_line = expand_variables(line, mo_shell);
	ft_putstr_fd(*expdd_line, fd);
	if (*expdd_line)
		(free(*expdd_line), *expdd_line = NULL);
}
