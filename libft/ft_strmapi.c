/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:52:14 by dsy               #+#    #+#             */
/*   Updated: 2019/10/23 18:12:07 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*stock;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (!(stock = ft_strdup(s)))
		return (NULL);
	i = 0;
	while (stock[i])
	{
		stock[i] = f(i, stock[i]);
		i++;
	}
	return (stock);
}
