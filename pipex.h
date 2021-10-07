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

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>

char	**ft_split_2(char const *s, char c, char *av);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
