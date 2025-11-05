/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:23:48 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * @brief Return the first occurrence of the char 'c' in the string 's'
 * 
 * @param s string to look at
 * @param c char to find
 * @return char* pointer to the first occurrence (NULL if not find)
 */
char	*ft_strchr(const char *s, int c)
{
	char	conv_c;

	conv_c = (char) c;
	while (*s != '\0' && *s != conv_c)
		s++;
	if (*s == conv_c)
		return ((char *) s);
	return (NULL);
}
