/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:14:50 by claprand          #+#    #+#             */
/*   Updated: 2024/06/05 21:30:12 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_conversion(va_list	*arg, char *s, int i)
{
	int	len;

	len = 0;
	if (s[i] == 'c')
		len = ft_print_char((int)va_arg(*arg, int));
	else if (s[i] == 's')
		len = ft_print_str((char *)va_arg(*arg, char *));
	else if (s[i] == 'd' || s[i] == 'i')
		len = ft_print_int((int)va_arg(*arg, int));
	else if (s[i] == 'x')
		len = ft_print_x((unsigned int)va_arg(*arg, unsigned int), s[i], &len);
	else if (s[i] == 'X')
		len = ft_printux((unsigned int)va_arg(*arg, unsigned int), s[i], &len);
	else if (s[i] == 'p')
		len = ft_print_pp((void *)va_arg(*arg, void *), &len);
	else if (s[i] == 'u')
		len = ft_print_u((unsigned int)va_arg(*arg, unsigned int));
	else if (s[i] == '%')
		len = ft_print_percent('%');
	return (len);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		len;
	va_list	arg;

	i = -1;
	len = 0;
	va_start(arg, s);
	while (s[++i])
	{
		if (s[i] == '%')
		{
			i++;
			len += ft_print_conversion(&arg, (char *)s, i);
			continue ;
		}
		else
			len += ft_print_char(s[i]);
	}
	va_end(arg);
	return (len);
}
