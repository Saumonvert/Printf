/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_balise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othabchi <othabchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:54:24 by idouidi           #+#    #+#             */
/*   Updated: 2019/12/13 19:25:57 by othabchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int		pars(char *str)
{
	int	i;
	i = 0;
	while (str[i] && !is_conversion(str[i]))
		i++;
	if (str[i] == 'd' || str[i] == 'i' || str[i] == 'u' || str[i] == 'x' ||
			str[i] == 'X' || str[i] == 'p')
		if (pars_nb(str) == 1)
			return (1);
	if (str[i] == 'c')
		if (pars_char(str) == 1)
			return (1);
	if (str[i] == 's')
		if (pars_str(str) == 1)
			return (1);
	return (0);
}

int			is_present(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !is_conversion(str[i]))
	{
		if (str[i - 1] && str[i] == '0' && str[i - 1] >= '0' && str[i - 1] <= '9')
			return (0);
		else if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_field		is_balise_flags(char *str, t_field field)
{
	if (is_present(str, '+') == 1)
		field.flags[0] = '+';
	else
		field.flags[0] = '/';
	if (is_present(str, '-') == 1)
		field.flags[1] = '-';
	else
		field.flags[1] = '/';
	if (is_present(str, ' ') == 1)
		field.flags[2] = ' ';
	else
		field.flags[2] = '/';
	if (is_present(str, '0') == 1)
		field.flags[3] = '0';
	else
		field.flags[3] = '/';
	return (field);
}

t_field		is_balise_width_n_precision(const char *str, t_field field)
{
	char		*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == '+' || str[i] == '-' || str[i] == ' '
				|| str[i] == '0'))
		i++;
	j = i;
	while (str[j] && str[j] >= '0' && str[j] <= '9')
		j++;
	tmp = ft_substr(str, i, j);
	field.width = ft_atoi(tmp);
	free(tmp);
	if (str[j] && str[j] == '.')
	{
		if (field.width == 0)
			field.flags[1] = '/';
		j++;
		i = j;
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
		tmp = ft_substr(str, j, i);
		printf("\n -----------------\n          %s       \n", tmp);
		field.precision = ft_atoi(tmp);
		free(tmp);
	}
	field.width = (field.precision > field.width) ? 0 : field.width;
	return (field);
}

t_field		is_balise(char *str)
{
	t_field field = {"0000", 0, 0, 0, 0};
	if (pars(str) == 0)
		field.error = 1;
	else
	{
		field = is_balise_flags(str, field);
		field = is_balise_width_n_precision(str, field);
	}
	return (field);
}
