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

#endif