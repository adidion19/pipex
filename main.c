/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:07:37 by adidion           #+#    #+#             */
/*   Updated: 2021/09/24 11:07:39 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

#include <stdio.h>

char	**ft_find_path(char **env)
{
	int i;
	char	**path;

	i = -1;
	while (ft_strncmp(env[++i], "PATH=", 5) != 0)
	{
		;
	}
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

void	ft_error_2(char **av)
{
	int	fd;

	fd = open(av[4], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFile doesn't exist, or you don't have the ", 1);
		ft_putstr_fd("right accesses to it\n", 1);
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error\nSomething went wrong\n", 1);
		exit(EXIT_FAILURE);
	}
}

void	ft_error(int ac, char **av)
{
	int	fd;

	if (ac != 5)
	{
		ft_putstr_fd("Error\nBad number of argumnts\n", 1);
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFile doesn't exist, or you don't have the ", 1);
		ft_putstr_fd("right accesses to it\n", 1);
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error\nSomething went wrong\n", 1);
		exit(EXIT_FAILURE);
	}
	ft_error_2(av);
}

int	main(int ac, char **av, char **env)
{
	char	**new_arg[2];
	char	**path;
	int	i;
	int fd[2];
	int pid1;
	int pid2;
	int file[2];

	ft_error(ac, av);
	file[1] = open(av[4], O_RDWR | O_TRUNC);
	if (file[1] == -1)
	{
		ft_putstr_fd("Error\nFile doesn't exist, or you don't have the ", 1);
		ft_putstr_fd("right accesses to it\n", 1);
		exit(EXIT_FAILURE);
	}
	file[0] = open(av[1], O_RDONLY);
	if (file[1] == -1)
	{
		ft_putstr_fd("Error\nFile doesn't exist, or you don't have the ", 1);
		ft_putstr_fd("right accesses to it\n", 1);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
		return (1);
	new_arg[0] = ft_split(av[2], ' ');
	new_arg[1] = ft_split(av[3], ' ');
	path = ft_find_path(env);
	i = -1;
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		dup2(file[0], 0);
		// close(fd[0]);
		while (path[++i])
		{
			path[i] = ft_strjoin(path[i], "/");
			path[i] = ft_strjoin(path[i], new_arg[0][0]);
			if (execve(path[i], new_arg[0], env) != -1)
				perror("Execve fail\n");
		}
	}
	i = -1;
	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		dup2(file[1], 1);
		// close(fd[0]);
		while (path[++i])
		{
			path[i] = ft_strjoin(path[i], "/");
			path[i] = ft_strjoin(path[i], new_arg[1][0]);
			if (execve(path[i], new_arg[1], env) != -1)
				perror("Execve fail\n");
		}
	}
	close(fd[0]);
	close(fd[1]);
	close(file[0]);
	close(file[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
