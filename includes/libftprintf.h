/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othabchi <othabchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:53:59 by dsy               #+#    #+#             */
/*   Updated: 2019/12/13 18:32:43 by othabchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFTPRINTF_H
# define FT_LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

extern int			g_return;

typedef struct		s_field {

	char	flags[4];
	int		width;
	int		precision;
	int		length;
	int		error;
}					t_field;

int					is_conversion(char c);
t_field				is_balise(char *str);
int					i_conversion(va_list params, char type, t_field field);
int					s_conversion(va_list params, char type, t_field field);
int					x_conversion(va_list params);
int					p_conversion(va_list params);
int					ft_printf(const char *format, ...);
unsigned long		ft_power(unsigned long x , unsigned long y);
void				ft_putnbr_x(unsigned long value);
void				print_balise_nb(int c, t_field field);
void				print_balise_str(char *str, t_field field);
void				print_balise_char(char c, t_field field);
int					pars_nb(char *str);
int					count_digit(int c);
int					pars_char(char *str);
int					pars_str(char *str);
int					check_balise(char c);

#endif
