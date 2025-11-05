/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:45:28 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * @brief Fill a memory space with 'len' value of 'c'
 * 
 * @param b memory space to fill
 * @param c used value to fill
 * @param len len to fill
 * @return void* pointer of filled memory space
 */
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	car;
	unsigned char	*ptr;

	car = c;
	ptr = b;
	i = 0;
	while (i < len)
		ptr[i++] = car;
	return (b);
}
