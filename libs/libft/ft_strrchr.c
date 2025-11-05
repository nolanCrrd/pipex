/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:24:06 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * @brief Locate the last occurrence of char 'c' int string 's'
 * 
 * @param s string to look at
 * @param c char to find
 * @return char* pointer to the last occurrence (NULL if not find)
 */
char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	conv_c;

	last = NULL;
	conv_c = (char) c;
	while (*s != '\0')
	{
		if (*s == conv_c)
			last = (char *) s;
		s++;
	}
	if (conv_c == '\0')
		return ((char *) s);
	return (last);
}
