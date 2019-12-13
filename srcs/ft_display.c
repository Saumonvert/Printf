/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othabchi <othabchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:24:32 by othabchi          #+#    #+#             */
/*   Updated: 2019/12/13 19:15:01 by othabchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void	print_balise_nb(int c, t_field field)
{
	int	width;
	int	precision;
	int	stock;

	if (count_digit(c) >= field.precision)
		field.precision = 0;
	precision = (field.precision = 0) ? count_digit(c) : field.precision - count_digit(c);
	stock = (field.flags[0] == '+' || field.flags[2] == ' ') ? precision + 1 : precision;
	// field.flags[2] == ' ' && c >= 0 ? ft_putchar(' ') : 0;
	if (field.flags[2] == ' ' && c >= 0)
	{
		ft_putchar(' ');
		g_return++;
	}
	width = (field.flags[0] == '+' || field.flags[2] == ' ') ? field.width - field.precision - 1 : field.width - field.precision;
	if (field.flags[1] != '-' && field.flags[3] != '0')
		while (width > 0 && width-- && g_return++)
				ft_putchar(' ');
	field.flags[0] == '+' ? ft_putchar('+') : 0;
	while (precision > 0 && precision-- && field.precision != 0 && g_return++)
		ft_putchar('0');
	if (field.flags[1] == '-')
	{
		ft_putnbr(c);
		g_return += c > 0 ? count_digit(c) : count_digit(c) + 1;
		while (width > 0 && width-- && field.precision != 0 && g_return++)
			ft_putchar(' ');
	}
	if (field.flags[3] == '0' && field.precision == 0)
		while (stock++ < field.width && g_return++)
			ft_putchar('0');
	if (field.flags[1] != '-')
	{
		ft_putnbr(c);
		g_return += c > 0 ? count_digit(c) : count_digit(c) + 1;
	}
	while (stock++ < field.width && width > 0 && field.precision == 0 && g_return++)
		ft_putchar(' ');
}

void	print_balise_str(char *str, t_field field)
{
	int	width;
	int	precision;
	int	len;
	int	cpy;
	int	i;

	i = 0;
	len = ft_strlen(str);
	precision = (field.precision > len) ? field.precision - len : len - field.precision;
	width = field.width - precision;
	cpy = (field.precision == 0) ? width : field.precision;
	if (field.width < len && field.precision == 0)
	{
		ft_putstr(str);
		g_return += len;
		return ;
	}
	if (field.width > field.precision && field.flags[1] != '-')
	{
		if (field.precision > 0)
			while (field.precision-- && g_return++)
				ft_putchar(' ');
		else
			while (width > 0 && width-- && g_return++)
				ft_putchar(' ');
	}
	while (cpy > 0 && cpy-- && g_return++)
	{
		ft_putchar(str[i]);
		i++;
	}
	if (field.width > field.precision && field.flags[1] == '-')
	{
		if (field.precision > 0)
			while (field.precision-- && g_return++)
				ft_putchar(' ');
		else
			while (width > 0 && width-- && g_return++)
				ft_putchar(' ');
	}
}

void	print_balise_char(char c, t_field field)
{
	int width;

	width = (field.width > 1) ? field.width - 1 : 0;
	if (field.flags[1] == '-')
	{
		ft_putchar(c);
		g_return++;
		while (width > 0 && width-- && g_return++)
			ft_putchar(' ');
	}
	else
	{
		while (width > 0 && width-- && g_return++)
			ft_putchar(' ');
		ft_putchar(c);
		g_return++;
	}
}
