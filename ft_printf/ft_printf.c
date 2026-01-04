/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:51:23 by anematol          #+#    #+#             */
/*   Updated: 2025/07/09 13:21:19 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_what(char type, va_list arg_list)
{
	if (type == 'c')
		return (ft_printf_c((char)va_arg(arg_list, int)));
	else if (type == 's')
		return (ft_printf_s(va_arg(arg_list, char *)));
	else if (type == 'p')
		return (ft_printf_p((uintptr_t)va_arg(arg_list, void *)));
	else if (type == 'i' || type == 'd')
		return (ft_printf_i(va_arg(arg_list, int)));
	else if (type == 'u')
		return (ft_printf_u(va_arg(arg_list, unsigned int)));
	else if (type == 'x')
		return (ft_printf_x(va_arg(arg_list, unsigned int), 0));
	else if (type == 'X')
		return (ft_printf_x(va_arg(arg_list, unsigned int), 1));
	else if (type == '%')
		return (ft_printf_c('%'));
	else
		return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg_list;
	int		j;
	int		len;

	if (!s)
		return (-1);
	len = 0;
	j = 0;
	va_start(arg_list, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			len += ft_printf_what(*(++s), arg_list) - 1;
			j++;
		}
		else
			write(1, s, 1);
		len++;
		s++;
	}
	va_end(arg_list);
	return (len);
}
