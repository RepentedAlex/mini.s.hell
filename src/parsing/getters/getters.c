/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:34:53 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/15 22:35:23 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

char	*get_var_content(char *var_name, char **env)
{
	int	i;
	int	j;

	i = 0;
	if (var_name[0] == '\0')
		return (NULL);
	while (env && env[i] && (ft_strncmp(var_name, env[i], \
		ft_strlen(var_name) + 1) != ('\0' - '=')))
		i++;
	if (env[i] == NULL)
		return (NULL);
	j = 0;
	while (env[i][j] != '=')
		j++;
	j++;
	return (ft_strdup(&env[i][j]));
}

int	get_var_len(char *src, t_mo_shell *mo_shell)
{
	int		i;
	int		ret;
	char	var_name[DEF_BUF_SIZ];
	char	*var_content;

	ft_bzero(var_name, DEF_BUF_SIZ);
	var_content = NULL;
	i = 0;
	while (src && src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
	{
		var_name[i] = src[i];
		i++;
	}
	var_content = get_var_content(var_name, mo_shell->shell_env);
	if (!var_content)
		return (0);
	ret = ft_strlen(var_content);
	free(var_content);
	return (ret);
}
