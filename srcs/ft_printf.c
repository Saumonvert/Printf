/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othabchi <othabchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:26:52 by dsy               #+#    #+#             */
/*   Updated: 2019/12/13 18:32:45 by othabchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int			g_return = 0;

static int	which_arg(char *str, va_list params)
{
	int		i;
	t_field	field;

	i = 0;
	field = is_balise(str);
	if (field.error == 1)
		return (0);
	while (str[i] && check_balise(str[i]))
		i++;
	if (str[i] == 'c' || str[i] == 's')
		if (!(s_conversion(params, str[i], field)))
			return (0);
	if (str[i] == 'i' || str[i] == 'd' || str[i] == 'u')
		if (!(i_conversion(params, str[i], field)))
			return (0);
	if (str[i] == 'p')
		if (!(p_conversion(params)))
			return (0);
	if (str[i] == 'x')
		if (!(x_conversion(params)))
			return (0);
	return (1);
}

static int	print_text(const char *str, va_list params)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i] == '%' && str[i + 1] == '%')
			i++;
		else if (str[i] == '%' && (check_balise(str[i + 1])
		|| is_conversion(str[i + 1])))
		{
			if (!(which_arg((char *)&str[i + 1], params)))
				return (0);
			i++;
			while (str[i] && !is_conversion(str[i]))
				i++;
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			g_return++;
			i++;
		}
	return (1);
}

int			ft_printf(const char *format, ...)
{
	va_list params;

	va_start(params, format);
	if (format == NULL)
		return (-1);
	if (!(print_text(format, params)))
		return (-1);
	va_end(params);
	return (g_return);
}
