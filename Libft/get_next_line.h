/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:20:55 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/02 12:21:09 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*get_next_line(int fd);
char		*ft_substr_m(char *s, unsigned int start, size_t len);
char		*ft_strdup_m(char *s1);
char		*ft_strjoin_m(char *s1, char*s2);
int			find_the_nl(char *s, int c);
size_t		ft_strlen_m(char *s);

#endif