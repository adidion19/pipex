/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:00:47 by adidion           #+#    #+#             */
/*   Updated: 2021/10/05 17:00:51 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (0);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

static int	len_(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_freee(int k, char *s1, char *s2)
{
	if (k == 3 || k == 1)
		free(s1);
	if (k == 3 || k == 2)
		free(s2);
}

char	*ft_strjoin(char *s1, char *s2, int k)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*str;

	i = -1;
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	len1 = len_((char *)s1);
	len2 = len_((char *)s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	j = i;
	i = -1;
	while (s2[++i])
		str[j++] = s2[i];
	str[j] = '\0';
	ft_freee(k, s1, s2);
	return (str);
}
