/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:20:13 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/10 17:20:17 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../Libft/include/libft.h"

/**
 * @brief Checks if single and double quotes are in pairs
 *
 * @param str The word.
 * @return `true` if there is an even number of quotes for single and double
 * `false` otherwise.
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

void	unquote_word(char *str, char *ret, int *quotes)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (!*quotes || (*quotes == 1 && str[i + j] == '\'') || \
				(*quotes == 2 && str[i + j] == '\"'))
		{
			check_in_quotes(str[i + j++], quotes);
			continue ;
		}
		if (((*quotes == 1 && str[i + j] == '\'') || \
				(*quotes == 2 && str[i + j] == '\"')) && j++)
			continue ;
		if ((*quotes == 2 && str[i + j] != '\"') || \
				(*quotes == 1 && str[i + j] != '\'') || !*quotes)
		{
			ret[i] = str[i + j];
			i++;
		}
	}
}

/**
 * @brief Removes "quotting" quotes.
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
	unquote_word(str, ret, &quotes);
	free(str);
	if (quotes)
		return (free(ret), NULL);
	return (ret);
}

/**
 * @brief Checks if word is quoted.
 *
 * @param word The word.
 * @return `true` if the word is quoted, `false` otherwise.
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
