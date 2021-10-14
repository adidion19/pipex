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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
	file = open(av[4], O_RDWR | O_TRUNC | O_CREAT);
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

void	ft_free(char ***s1, char **path)
{
	int	i;
	int	j;

	i = -1;
	while (path[++i])
		free(path[i]);
	i = -1;
	j = -1;
	while (s1[++i])
	{
		j = -1;
		while (s1[i][++j])
			;
		free_t(s1[i], j);
	}
	free(path);
}

int	ft_file_2(char **av)
{
	int	file;

	file = open(av[1], O_RDONLY);
	if (file == -1)
	{
		ft_putstr_fd("Error\nFile doesn't exist, or you don't have the ", 1);
		ft_putstr_fd("right accesses to it\n", 1);
		exit(EXIT_FAILURE);
	}
	return (file);
}

int	ft_second_command(int *fd, int *file, char **path, char ***new_arg, char **env)
{
	int	pid2;
	int	acces;
	int	i;

	pid2 = fork();
	if (pid2 < 0)
		return (0);
	acces = 0;
	i = -1;
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		dup2(file[1], 1);
		close(fd[0]);
		while (path[++i])
		{
			path[i] = ft_strjoin(path[i], "/", 0);
			path[i] = ft_strjoin(path[i], new_arg[1][0], 1);
			if (execve(path[i], new_arg[1], env) == -1)
				acces++;
		}
	}
	if (acces == i)
		write(2, "Error\nWrong second command\n", 27);
	if (acces == i)
		exit(EXIT_FAILURE);
	return (pid2);
}

int	ft_first_command(int *fd, int *file, char **path, char ***new_arg, char **env)
{
	int	pid1;
	int	acces;
	int	i;

	pid1 = fork();
	acces = 0;
	if (pid1 < 0)
		return (0);
	acces = 0;
	i = -1;
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		dup2(file[0], 0);
		close(fd[0]);
		while (path[++i])
		{
			path[i] = ft_strjoin(path[i], "/", 0);
			path[i] = ft_strjoin(path[i], new_arg[0][0], 1);
			if (execve(path[i], new_arg[0], env) == -1)
				acces++;
		}
	}
	if (acces == i)
		write(2, "Error\nWrong first command\n", 26);
	if (acces == i)
		exit(EXIT_FAILURE);
	return (pid1);
}

int	main(int ac, char **av, char **env)
{
	char	**new_arg[2];
	char	**path;
	int		fd[2];
	int		file[2];
	int		pid[2];

	file[1] = ft_error(ac, av);
	file[0] = ft_file_2(av);
	if (pipe(fd) == -1)
		return (1);
	new_arg[0] = ft_split(av[2], ' ');
	new_arg[1] = ft_split(av[3], ' ');
	path = ft_find_path(env);
	pid[0] = ft_first_command(fd, file, path, new_arg, env);
	pid[1] = ft_second_command(fd, file, path, new_arg, env);
	close(fd[0]);
	close(fd[1]);
	close(file[0]);
	close(file[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	ft_free(new_arg, path);
}
