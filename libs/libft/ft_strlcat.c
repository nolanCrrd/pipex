/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:23:52 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * @brief put the 'src' at the end of 'dst' in the 'dstsize' limit
 * 
 * @param dst string to receive a suffix
 * @param src suffix
 * @param dstsize allocated size of dst
 * @return size_t size that dst should have after the concatenation
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (dst_len >= dstsize)
		return (dstsize + ft_strlen(src));
	i = dst_len;
	while (i < dstsize - 1 && src[i - dst_len])
	{
		dst[i] = src[i - dst_len];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (dst_len + ft_strlen(src));
}
