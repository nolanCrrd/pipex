/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 02:26:14 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/04 17:46:31 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h>

static void	set_reverse_number(char tmp_buffer[11], int n, int *i)
{
	unsigned int	converted_n;

	converted_n = n * ((n < 0) * -2 + 1);
	*i = 0;
	if (converted_n == 0)
		tmp_buffer[(*i)++] = '0';
	while (converted_n > 0)
	{
		tmp_buffer[(*i)++] = converted_n % 10 + '0';
		converted_n /= 10;
	}
	tmp_buffer[*i] = '\n';
}

/**
 * @brief convert an int into a string
 * 
 * @param n value in int to convert
 * @return char* converted string
 */
char	*ft_itoa(int n)
{
	char	*buffer;
	char	tmp_buffer[11];
	int		real_len;
	int		j;
	int		is_negative;

	is_negative = n < 0;
	set_reverse_number(tmp_buffer, n, &real_len);
	buffer = malloc(real_len + 1 + is_negative);
	if (buffer == NULL)
		return (NULL);
	j = 0;
	if (is_negative)
		buffer[j++] = '-';
	while (--real_len >= 0)
		buffer[j++] = tmp_buffer[real_len];
	buffer[j] = '\0';
	return (buffer);
}
