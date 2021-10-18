/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:13:43 by adidion           #+#    #+#             */
/*   Updated: 2021/10/18 15:13:46 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_find_path(char **env)
{
	int		i;
	char	**path;

	i = -1;
	while (ft_strncmp(env[++i], "PATH=", 5) != 0)
		;
	path = ft_split((env[i]) + 5, ':');
	return (path);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (s && fd)
	{
		while (s[++i])
			write(fd, &s[i], 1);
	}
}

int	ft_error(int ac, char **av)
{
	int	file;

	if (ac != 5)
	{
		ft_putstr_fd("Error\nBad number of argumnts\n", 1);
		exit(EXIT_FAILURE);
	}
	file = open(av[4], O_RDWR | O_TRUNC | O_CREAT | 00777);
	if (file == -1)
	{
		ft_putstr_fd("Error\nFile doesn't exist, or you don't have the ", 1);
		ft_putstr_fd("right accesses to it\n", 1);
		exit(EXIT_FAILURE);
	}
	return (file);
}

char	**free_t(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	exit(EXIT_SUCCESS);
}

void	ft_free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}
