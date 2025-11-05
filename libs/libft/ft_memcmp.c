/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:23:37 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * @brief Compare 2 memory space, like strcmp
 * 
 * @param s1 memory space 1
 * @param s2 memory space 2
 * @param n number of bytes to compare
 * @return int the difference between 2 different elements (0 if same)
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	size_t			i;

	i = 0;
	s1_ptr = (unsigned char *) s1;
	s2_ptr = (unsigned char *) s2;
	while (i < n && s1_ptr[i] == s2_ptr[i])
		i++;
	if (i == n)
		return (0);
	return (s1_ptr[i] - s2_ptr[i]);
}
