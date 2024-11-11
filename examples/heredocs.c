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

/**
 * @brief Remove "quotting" quotes.
 *
 * @param str The string we want to get rid of quotes.
 * @return The remaining of the string without quotes or NULL on error (quotes left open count as an error).
 */
char	*remove_quotes(char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		quotes;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	quotes = 0;
	while (str[i + j])
	{
		if (!quotes || (quotes == 1 && str[i + j] == '\'') || (quotes == 2 && str[i + j] == '\"'))
		{
			check_in_quotes(str[i + j], &quotes); //Doesn't give the proper information to skip quoting quotes
			j++;
			continue ;
		}
		if ((quotes == 1 && str[i + j] == '\'') || (quotes == 2 && str[i + j] == '\"'))
		{
			j++;
			continue ;
		}
		if ((quotes == 2 && str[i + j] != '\"') || (quotes == 1 && str[i + j] != '\'') || !quotes)
		{
			ret[i] = str[i + j];
			i++;
		}
	}
	free(str);
	if (quotes)
		return (free(ret), NULL);
	return (ret);
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

char	*heredoc(t_block *block, t_cmd *cmd, char **envp)
{
	char	*buffer;
	char	*line;
	char	*ret;
	bool	quoted_word;

	//UNHAPPY CODE
	if (!block->str)
		ft_putstr_fd("Invalid word\n", 2);

	//HAPPY CODE
	line = NULL;
	buffer = NULL;
	ret = NULL;
	//Check if word is quoted (if quoted, no expansion)
	quoted_word = check_if_word_is_quoted(block->str);
	if (quoted_word)
	{
		block->str = remove_quotes(block->str);
	}
	else
	{
		expand_variables(block->str, envp, NULL);
	}
	while (1) //Not sure if while true is a wonderful idea
	{
		line = readline("> ");

		//BREAK CONDITION
		if (ft_strcmp(line, block->str) == 0)
			break ;
	}
	return (ret);
}

int	main(int argc, char **envp)
{
	t_block block;

	block.str = ft_strdup("\"\"");
	heredoc(&block, NULL, envp);
}
