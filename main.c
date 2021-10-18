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

void	ft_free_arg(char ***s1, int bool)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (s1[++i])
	{
		j = -1;
		while (s1[i][++j])
			;
		free_t(s1[i], j);
	}
	if (bool == 1)
		exit(EXIT_FAILURE);
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

int	ft_second_command(int *fd, int *file, char ***new_arg, char **env)
{
	int		pid2;
	int		acces;
	int		i;
	char	**path;

	path = ft_find_path(env);
	pid2 = fork();
	if (pid2 < 0)
		ft_free_arg(new_arg, 1);
	acces = 0;
	i = -1;
	if (pid2 == 0)
	{
		ft_second_utils(fd[0], fd[1], file[1]);
		while (path[++i])
		{
			path[i] = ft_strjoin(path[i], "/", 0);
			path[i] = ft_strjoin(path[i], new_arg[1][0], 1);
			if (execve(path[i], new_arg[1], env) == -1)
				acces++;
		}
	}
	ft_error_command_two(acces, i, new_arg);
	ft_free_path(path);
	return (pid2);
}

int	ft_first_command(int *fd, int *file, char ***new_arg, char **env)
{
	int		pid1;
	int		acces;
	int		i;
	char	**path;

	pid1 = fork();
	acces = 0;
	if (pid1 < 0)
		ft_free_arg(new_arg, 1);
	path = ft_find_path(env);
	i = -1;
	if (pid1 == 0)
	{
		ft_first_utils(fd[0], fd[1], file[1]);
		while (path[++i])
		{
			path[i] = ft_strjoin(path[i], "/", 0);
			path[i] = ft_strjoin(path[i], new_arg[0][0], 1);
			if (execve(path[i], new_arg[0], env) == -1)
				acces++;
		}
	}
	ft_error_command_one(acces, i, new_arg);
	ft_free_path(path);
	return (pid1);
}

int	main(int ac, char **av, char **env)
{
	char	**new_arg[2];
	int		fd[2];
	int		file[2];
	int		pid[2];
	int		status;

	file[1] = ft_error(ac, av);
	file[0] = ft_file_2(av);
	if (pipe(fd) == -1)
		return (1);
	new_arg[0] = ft_split(av[2], ' ');
	new_arg[1] = ft_split(av[3], ' ');
	pid[0] = ft_first_command(fd, file, new_arg, env);
	pid[1] = ft_second_command(fd, file, new_arg, env);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	close(file[0]);
	close(file[1]);
	ft_free_arg(new_arg, 0);
}
