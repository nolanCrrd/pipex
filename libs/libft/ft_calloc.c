/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:23:22 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief malloc a memory space of count * size bytes and fill them with zero
	if (count != 0 && size <= SIZE_MAX / count)
 * 
 * @param count number of elements
 * @param size size of each element
 * @return void* pointer to the allocated memory space (NULL if malloc fail)
 */
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = NULL;
	if (size == 0 || count == 0)
		return (malloc(0));
	if (size <= SIZE_MAX / count)
		ptr = malloc(size * count);
	if (ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	ft_bzero(ptr, size * count);
	return ((void *) ptr);
}
