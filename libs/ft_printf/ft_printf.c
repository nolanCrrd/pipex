/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:42:34 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/06 13:13:37 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>

int	is_valid_format(char c)
{
	return (c == 'c' || c == 's' || c == 'u' || c == 'i'
		|| c == 'x' || c == '%' || c == 'X' || c == 'p' || c == 'd');
}

void	print_correct_format(const char	*fmt, va_list *args, long *nb_write, int fd)
{
	char	*buffer;
	char	tmp;

	if (*fmt != 'c' && *fmt != '%')
	{
		if (*fmt == 's')
			buffer = get_str_or_null(va_arg(*args, char *));
		else if (*fmt == 'i' || *fmt == 'd')
			buffer = ft_lltoa(va_arg(*args, int));
		else if (*fmt == 'u')
			buffer = ft_ulltoa(va_arg(*args, unsigned int));
		else if (*fmt == 'x' || *fmt == 'X')
			buffer = ft_xtoa(va_arg(*args, unsigned int), *fmt == 'X');
		else
			buffer = ft_addtoa(va_arg(*args, unsigned long long));
		*nb_write = write(fd, buffer, ft_strlen(buffer));
	}
	else if (*fmt == '%')
		*nb_write = write(fd, "%", 1);
	else
	{
		tmp = va_arg(*args, int);
		*nb_write = write(fd, &tmp, 1);
	}
}

static int	ft_vdprintf(int fd, const char *fmt, va_list *args)
{
	long	wrote_number;
	long	current_write;

	wrote_number = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (is_valid_format(*fmt))
				print_correct_format(fmt, args, &current_write, fd);
			else
				current_write = ft_dprintf(fd, "%%%c", *fmt);
		}
		else
			current_write = write(fd, fmt, 1);
		if (current_write < 0)
			return (E_WRITING_ERR);
		wrote_number += current_write;
		fmt++;
	}
	return (wrote_number);
}

int	ft_dprintf(int fd, const char *fmt, ...)
{
	long	wrote_number;
	va_list	arg;

	va_start(arg, fmt);
	wrote_number = ft_vdprintf(fd, fmt, &arg);
	va_end(arg);
	return (wrote_number);
}

int	ft_printf(const char *fmt, ...)
{
	long	wrote_number;
	va_list	arg;

	va_start(arg, fmt);
	wrote_number = ft_vdprintf(STDOUT_FILENO, fmt, &arg);
	va_end(arg);
	return (wrote_number);
}
