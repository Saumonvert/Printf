# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djsy <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 16:31:35 by djsy              #+#    #+#              #
#    Updated: 2019/12/03 23:49:21 by dsy              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

OBJS = srcs/ft_printf.o srcs/ft_printf_conv.o srcs/ft_is_balise.o srcs/ft_pars.o srcs/ft_utils.o srcs/ft_display.o libft/*.o

SRCS = srcs/ft_printf.c srcs/ft_printf_conv.c srcs/ft_is_balise.c srcs/ft_utils.c srcs/ft_display.c srcs/ft_pars.c 

all:
	@cd libft/ && make
	@gcc -Wall -Werror -Wextra $(SRCS) -c 
	@mv ft_printf.o srcs/
	@mv ft_printf_conv.o srcs/
	@mv ft_is_balise.o srcs/
	@mv ft_pars.o srcs/
	@mv ft_utils.o srcs/
	@mv ft_display.o srcs/
	@ar rcs $(NAME) $(OBJS)

clean:
	@/bin/rm -f $(OBJS)
	@cd libft/ && make clean

fclean: clean
	@cd libft/ && make fclean
	@/bin/rm -f $(NAME)

re: fclean all
