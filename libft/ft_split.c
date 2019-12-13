/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:48:49 by dsy               #+#    #+#             */
/*   Updated: 2019/10/24 14:20:00 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_words(char *str, char c)
{
	int		i;
	int		word;
	int		wflag;

	i = 0;
	word = 0;
	wflag = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			if (!wflag)
			{
				wflag = 1;
				word++;
			}
		}
		else
			wflag = 0;
		i++;
	}
	return (word);
}

static char	*cut_word(char *str, char c)
{
	int		i;
	int		j;
	char	*str_return;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	j = i;
	i = 0;
	if ((str_return = (char*)malloc(sizeof(char) * j + 1)) == NULL)
		return (NULL);
	while (i < j)
	{
		str_return[i] = str[i];
		i++;
	}
	str_return[i] = '\0';
	return (str_return);
}

static char	*get_word(char *str, int w, char c)
{
	int		i;
	int		word;
	int		wflag;

	i = 0;
	word = 0;
	wflag = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			if (!wflag)
			{
				wflag = 1;
				word++;
				if (word == w)
					return (cut_word(&str[i], c));
			}
		}
		else
			wflag = 0;
		i++;
	}
	return (&str[i]);
}

char		**ft_split(char const *str, char c)
{
	int		i;
	int		k;
	char	*newstr;
	char	**tab;

	i = 0;
	if (!str || (tab = (char**)malloc(sizeof(char*) *
					(get_words((char *)str, c) + 1)))
			== NULL)
		return (NULL);
	while (i < get_words((char *)str, c))
	{
		k = 0;
		newstr = get_word((char *)str, i + 1, c);
		while (newstr[k])
			k++;
		if ((tab[i] = (char*)malloc(sizeof(char) * k + 1)) == NULL)
			return (NULL);
		tab[i] = newstr;
		tab[i][k] = '\0';
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
