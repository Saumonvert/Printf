/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othabchi <othabchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:31:22 by dsy               #+#    #+#             */
/*   Updated: 2020/01/16 20:50:13 by othabchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libftprintf.h"
#include <stdio.h>

int main()
{
	printf("[%d]\n", ft_printf("%d - %i - %u - %x - %X - %c - %s - %%", -5, -5, -5, -5, -5, '\0', NULL));
	printf("[%d]\n", printf("%d - %i - %u - %x - %X - %c - %s - %%", -5, -5, -5, -5, -5, '\0', NULL));

	// printf("[%d]\n", ft_printf("%10s", "hello"));
	// printf("[%d]\n", printf("%10s", "hello"));

	// printf("[%d]\n", ft_printf("%.10s", "hello"));
	// printf("[%d]\n", printf("%.10s", "hello"));

	// printf("[%d]\n", ft_printf("%15.10s", "hello"));
	// printf("[%d]\n", printf("%15.10s", "hello"));

	// printf("[%d]\n", ft_printf("%*.*s", 15, 10, "hello"));
	// printf("[%d]\n", printf("%*.*s", 15, 10, "hello"));

	return (0);
}
