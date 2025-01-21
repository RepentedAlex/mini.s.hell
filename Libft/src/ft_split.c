/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:09:26 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:33:37 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Counts the number of tokens in a string based on a given separator.
 *
 * @param str The string to count tokens from.
 * @param sep The separator character.
 * @return The number of tokens in the string.
 */
static size_t	ft_count_tokens(char const *str, char sep)
{
	int	token_count;
	int	i;
	int	is_word;

	token_count = 0;
	i = 0;
	is_word = 0;
	if (str[i] && str[i] != sep)
	{
		is_word = 1;
		token_count++;
	}
	while (str[i])
	{
		if (str[i] != sep && !is_word)
		{
			is_word = 1;
			token_count++;
		}
		else if (str[i] == sep && is_word)
			is_word = 0;
		i++;
	}
	return (token_count);
}

/**
 * @brief Copies a word from a string separated by a given character.
 *
 * This function copies a word from a string,
 * where words are separated by a specified character.
 * It starts copying from the first non-separator character and
 * stops at the next separator character or the end of the string.
 * The copied word is allocated dynamically using
 * ft_calloc() and must be freed by the caller.
 *
 * @param str The string to copy the word from.
 * @param sep The separator character.
 * @param p   A pointer to a size_t variable to store the index
 * of the next character after the copied word.
 *
 * @return A dynamically allocated string containing the copied word,
 * or NULL if memory allocation fails.
 */
static char	*ft_copy_words(const char *str, char sep, size_t *p)
{
	size_t	i;
	size_t	len_and_j;
	char	*word;

	i = 0;
	len_and_j = 0;
	while (str[i] && str[i] == sep)
		i++;
	while (str[i] && str[i] != sep)
	{
		len_and_j++;
		i++;
	}
	word = ft_calloc(len_and_j + 1, sizeof(char));
	if (!word)
		return (NULL);
	i -= len_and_j;
	len_and_j = 0;
	while (str[i] && str[i] != sep)
		word[len_and_j++] = str[i++];
	*p = i;
	word[len_and_j] = 0;
	return (word);
}

/**
 * @brief Frees the memory allocated for a dynamically allocated string array.
 *
 * This function takes a dynamically allocated string array as input and frees
 * the memory allocated for each string in the array, as well as the memory
 * allocated for the array itself.
 *
 * @param tab The string array to be freed.
 */
static void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/**
 * Splits a string into an array of tokens based on a delimiter character.
 *
 * @param s The string to split.
 * @param c The delimiter character.
 * @return An array of tokens, or NULL if memory allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	char	**tokens_array;
	size_t	token_count;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	token_count = (ft_count_tokens(s, c));
	tokens_array = ft_calloc(token_count + 1, sizeof(char *));
	if (!tokens_array)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		tokens_array[i] = ft_copy_words(s, c, &j);
		if (!tokens_array[i])
		{
			ft_free_tab(tokens_array);
			return (NULL);
		}
		s += j;
		i++;
	}
	tokens_array[i] = NULL;
	return (tokens_array);
}
