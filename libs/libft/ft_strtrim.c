/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 02:26:34 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

/**
 * @brief delete given 'set' of char at start and end of a string
 * 
 * @param s1 string to trim
 * @param set set of char to delete
 * @return char* pointer to trimmed string (NULL if malloc fail)
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*trimmed_str;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1) != NULL)
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len - 1]))
		len--;
	trimmed_str = malloc(len + 1);
	if (trimmed_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trimmed_str[i] = s1[i];
		i++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}
