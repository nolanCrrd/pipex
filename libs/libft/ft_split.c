/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 02:26:24 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

static size_t	count_word(char const *s, char c)
{
	size_t	nb_word;

	if (*s && *s != c)
		nb_word = 1;
	else
		nb_word = 0;
	while (*s && *(s + 1))
	{
		if (*s == c && *(s + 1) != c)
			nb_word++;
		s++;
	}
	return (nb_word);
}

static char	**clear(char **strs, size_t j)
{
	size_t	count;

	count = 0;
	if (strs[j] == NULL)
	{
		j--;
		while (count <= j)
			free(strs[count++]);
		free(strs);
		return (NULL);
	}
	return (strs);
}

static char	**fill_word(char const *s, char c, char **strs, size_t	*j)
{
	size_t	i;
	size_t	last_word;

	i = 0;
	last_word = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i != 0 && s[i - 1] != c)
			{
				strs[(*j)++] = ft_substr(s, last_word, i - last_word);
				if (clear(strs, *j - 1) == NULL)
					return (NULL);
			}
			last_word = i + 1;
		}
		i++;
	}
	if (i != 0 && s[i - 1] != c)
		strs[(*j)++] = ft_substr(s, last_word, i - last_word);
	strs[*j] = NULL;
	return (strs);
}

/**
 * @brief Separate the given string by the separator 'c' and put
 * each splitted string into an array
 * 
 * @param s string to split
 * @param c separator
 * @return char** array (NULL if malloc fail)
 */
char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	j;

	if (s == NULL)
		return (NULL);
	strs = malloc(sizeof(char *) * (count_word(s, c) + 1));
	j = 0;
	if (strs == NULL)
		return (NULL);
	strs = fill_word(s, c, strs, &j);
	if (j != 0 && clear(strs, j - 1) == NULL)
		return (NULL);
	return (strs);
}
