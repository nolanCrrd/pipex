/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:23:35 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * @brief return the first occurrence of 'c' in 's'
 * 
 * @param s memory space where search
 * @param c value to find
 * @param n size of the memory space to check
 * @return void* the location of the first occurrence (NULL if not find)
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	size_t			i;
	unsigned char	car;

	i = 0;
	s_ptr = (unsigned char *) s;
	car = (unsigned char) c;
	while (i < n && s_ptr[i] != car)
		i++;
	if (i != n && s_ptr[i] == car)
		return ((void *) &s_ptr[i]);
	return (NULL);
}
