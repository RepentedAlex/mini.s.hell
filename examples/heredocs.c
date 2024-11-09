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

size_t	count_quotes(const char *str)
{
	int		i;
	size_t	quote_count;

	quote_count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote_count++;
	}
	return (quote_count);
}

void	remove_quotes(char *str)
{
	char	*ret;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(str);
	len -= count_quotes(str);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return ;
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i + j] == '\'' || str[i + j] == '\"')
		{
			j++;
		}
		ret[i] = str[i + j];
		i++;
	}
}

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

char	*heredoc(t_block *block, t_cmd *cmd)
{
	char	*buffer;
	char	*line;
	char	*ret;
	bool	quoted_word;
	bool	wrong_quote_count;

	//UNHAPPY CODE
	if (!block->str)
		ft_putstr_fd("Invalid word\n", 2);

	//HAPPY CODE
	line = NULL;
	buffer = NULL;
	ret = NULL;
	wrong_quote_count = false;
	//Check if word is quoted (if quoted, no expansion)
	quoted_word = check_if_word_is_quoted(block->str);
	if (quoted_word)
	{
		wrong_quote_count = !check_good_number_quotes(block->str);
		remove_quotes(block->str);
	}
	while (1) //Not sure if while true is a wonderful idea
	{
		line = readline("> ");

		//BREAK CONDITION
		if (!wrong_quote_count && ft_strcmp(line, block->str) == 0)
			break ;
	}
	return (ret);
}

int	main(void)
{
	t_block block;

	block.str = "EOF";
	heredoc(&block, NULL);
}
