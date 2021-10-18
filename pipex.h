/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:31:40 by adidion           #+#    #+#             */
/*   Updated: 2021/09/24 11:31:42 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <limits.h>

char	**ft_split_2(char const *s, char c, char *av);
char	*ft_strjoin(char *s1, char *s2, int k);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
void	ft_error_command_one(int acces, int i, char ***new_arg);
void	ft_first_utils(int fd, int fd1, int file);
void	ft_second_utils(int fd, int fd1, int file);
void	ft_error_command_two(int acces, int i, char ***new_arg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_free_path(char **path);
void	ft_putstr_fd(char *s, int fd);
int		ft_error(int ac, char **av);
char	**free_t(char **tab, int j);
char	**ft_find_path(char **env);
void	ft_free_arg(char ***s1, int bool);

#endif