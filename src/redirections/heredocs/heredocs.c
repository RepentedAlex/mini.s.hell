/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:47:55 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/20 14:06:21 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../Libft/include/libft.h"

size_t	ft_hash_djb2(const void *key, size_t size)
{
	unsigned char	*str;
	size_t			hash;

	hash = 5381;
	str = (unsigned char *)key;
	while (size--)
		hash = (hash << 5) + hash + str[size];
	return (hash);
}

char	*create_hd_fnm(const t_cmd *cmd)
{
	size_t	hash;
	char	*path;
	char	*hdoc_id;

	hdoc_id = NULL;
	path = ft_strdup("/tmp/heredoc");
	hash = ft_hash_djb2((const void *)cmd, ft_strlen((char *)cmd));
	hdoc_id = (char *)malloc(sizeof(char) * 3);
	if (!hdoc_id)
		return (NULL);
	hdoc_id[0] = (char)((char)hash % 256);
	hdoc_id[1] = (char)((char)hash % 100);
	hdoc_id[2] = '\0';
	return (append(path, hdoc_id, 1));
}

/**
 * @brief Checks if the word is quoted and unquotes it necessary, otherwise
 * it expands the word if pertinent.
 *
 * @param str The heredoc's word.
 * @param envp The environment variables.
 * @param mo_shell The mo_shell structure.
 */
void	heredoc_expand_word(char *str, char *envp[], t_mo_shell *mo_shell)
{
	char	*tmp;

	tmp = expand_variables(str, envp, mo_shell);
	free(str);
	str = tmp;
	tmp = NULL;
}

/**
 * @brief Handles the heredoc.
 *
 * @param block The current t_block node we're on.
 * @param cmd The current t_cmd node we're on.
 * @param envp The environment variables.
 */
int	heredoc(t_block *block, t_cmd *cmd, t_mo_shell *mo_shell)
{
	int		hd_fd;
	char	*line;
	bool	quoted_word;

	if (!block->str)
		ft_putstr_fd("Invalid word\n", 2);
	quoted_word = check_if_word_is_quoted(block->str);
	if (quoted_word)
		block->str = remove_quotes(block->str);
	else
		heredoc_expand_word(block->str, mo_shell->shell_env, NULL);
	hd_fd = open(create_hd_fnm(cmd), O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, block->str) == 0)
			break ;
		write(hd_fd, line, ft_strlen(line));
		write(hd_fd, "\n", 1);
	}
	cmd->fd_i = hd_fd;
	return (hd_fd);
}
