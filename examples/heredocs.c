/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:47:55 by apetitco          #+#    #+#             */
/*   Updated: 2024/11/09 00:47:57 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../Libft/include/libft.h"

/**
 * @brief 
 *
 * @param str 
 * @return 
 */
bool	check_good_number_quotes(const char *str)
{
	int	i;
	int	single_quote_count;
	int	double_quote_count;

	single_quote_count = 0;
	double_quote_count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			single_quote_count++;
		else if (str[i] == '\"')
			double_quote_count++;
	}
	if (single_quote_count % 2 != 0 || double_quote_count % 2 != 0)
		return (false);
	return (true);
}

void	do_work(char *str, char *ret, int *quotes)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (!quotes || (*quotes == 1 && str[i + j] == '\'') || \
				(*quotes == 2 && str[i + j] == '\"'))
		{
			check_in_quotes(str[i + j++], quotes);
			continue ;
		}
		if ((*quotes == 1 && str[i + j] == '\'') || \
				(*quotes == 2 && str[i + j] == '\"'))
		{
			j++;
			continue ;
		}
		if ((*quotes == 2 && str[i + j] != '\"') || \
				(*quotes == 1 && str[i + j] != '\'') || !quotes)
			ret[i] = str[i++ + j];
	}
}

/**
 * @brief Remove "quotting" quotes.
 *
 * @param str The string we want to get rid of quotes.
 * @return The remaining of the string without quotes or NULL on error 
 * (quotes left open count as an error).
 */
char	*remove_quotes(char *str)
{
	char	*ret;
	int		quotes;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ret)
		return (NULL);
	quotes = 0;
	do_work(str, ret, &quotes);
	free(str);
	if (quotes)
		return (free(ret), NULL);
	return (ret);
}

/**
 * @brief 
 *
 * @param word 
 * @return 
 */
bool	check_if_word_is_quoted(const char *word)
{
	int	i;

	i = -1;
	while (word[++i])
	{
		if (word[i] == '\'' || word[i] == '\"')
			return (true);
	}
	return (false);
}

/**
 * @brief 
 *
 * @param str 
 * @param envp 
 * @param mo_shell 
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
 * @brief 
 *
 * @param block 
 * @param cmd 
 * @param envp 
 */
void	heredoc(t_block *block, t_cmd *cmd, char **envp)
{
	int		heredoc_fd;
	char	*line;
	bool	quoted_word;

	if (!block->str)
		ft_putstr_fd("Invalid word\n", 2);
	quoted_word = check_if_word_is_quoted(block->str);
	if (quoted_word)
		block->str = remove_quotes(block->str);
	else
		heredoc_expand_word(block->str, envp, NULL);
	heredoc_fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, block->str) == 0)
			break ;
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
	}
}

int	main(int argc, char **envp)
{
	t_block	block;

	block.str = ft_strdup("\"$USER\"");
	heredoc(&block, NULL, envp);
}
