/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:06:59 by adidion           #+#    #+#             */
/*   Updated: 2021/10/18 15:07:01 by adidion          ###   ########.fr       */
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

void	ft_error_command_two(int acces, int i, char ***new_arg)
{
	if (acces == i)
		write(2, "Error\nWrong second command\n", 27);
	if (acces == i)
		ft_free_arg(new_arg, 1);
}

void	ft_second_utils(int fd, int fd1, int file)
{
	dup2(fd, STDIN_FILENO);
	close(fd1);
	dup2(file, 1);
	close(fd1);
}

void	ft_error_command_one(int acces, int i, char ***new_arg)
{
	if (acces == i)
		write(2, "Error\nWrong first command\n", 26);
	if (acces == i)
		ft_free_arg(new_arg, 1);
}

void	ft_first_utils(int fd, int fd1, int file)
{
	dup2(fd1, STDOUT_FILENO);
	close(fd);
	dup2(file, 0);
	close(fd1);
}
