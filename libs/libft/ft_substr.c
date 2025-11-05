/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:40:05 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

/**
 * @brief Duplicate 'len' char from the given string but only 
 * from the index 'start'
 * 
 * @param s string to duplicate
 * @param start start index of duplication
 * @param len number of char after start
 * @return char* allocated string (NULL if malloc fail)
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*new;
	size_t			size;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	size -= start;
	if (size < len)
		new = ft_calloc(1, size + 1);
	else
		new = ft_calloc(1, len + 1);
	if (len == 0 || new == NULL)
		return (new);
	j = 0;
	i = 0;
	if (s[start + i] != '\0')
	{
		while (s[i] && j < len)
			new[j++] = s[start + i++];
	}
	return (new);
}
