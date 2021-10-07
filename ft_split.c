/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 11:16:34 by adidion           #+#    #+#             */
/*   Updated: 2021/10/05 11:16:35 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int		in_string(char c, char c2)
{
	if (c == c2)
		return (1);
	return (0);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int		count_word(char *str, char charset)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (in_string(str[i], charset))
			i++;
		if (!(in_string(str[i], charset)) && str[i] != 0)
		{
			while (!(in_string(str[i], charset)) && str[i])
				i++;
			count++;
		}
	}
	return (count);
}

static char		**free_tab(char **tab, int j)
{
	int i;

	i = 0;
	while (i < j && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	exit(EXIT_FAILURE);
}

char			**ft_split_2(char const *s, char c, char *av)
{
	int		i;
	int		j;
	int		index;
	char	**tab;

	i = 0;
	j = 0;
	index = 0;
	tab = 0;
	if (!s || !(tab = malloc(sizeof(*tab) * (count_word((char*)s, c) + 2))))
		exit(EXIT_FAILURE);
	while (index < count_word((char*)s, c))
	{
		if (!(tab[index] = malloc(sizeof(char) * (ft_strlen((char*)s) + 1))))
			return (free_tab(tab, i));
		while (s[i] && in_string(((char*)s)[i], c))
			i++;
		while (s[i] && !in_string(((char*)s)[i], c))
			tab[index][j++] = s[i++];
		tab[index++][j] = '\0';
		j = 0;
	}
	tab[index++] = ft_strjoin(av, "");
	tab[index] = 0;
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		index;
	char	**tab;

	i = 0;
	j = 0;
	index = 0;
	tab = 0;
	if (!s || !(tab = malloc(sizeof(*tab) * (count_word((char*)s, c) + 2))))
		exit(EXIT_FAILURE);
	while (index < count_word((char*)s, c))
	{
		if (!(tab[index] = malloc(sizeof(char) * (ft_strlen((char*)s) + 1))))
			return (free_tab(tab, i));
		while (s[i] && in_string(((char*)s)[i], c))
			i++;
		while (s[i] && !in_string(((char*)s)[i], c))
			tab[index][j++] = s[i++];
		tab[index++][j] = '\0';
		j = 0;
	}
	tab[index] = 0;
	return (tab);
}