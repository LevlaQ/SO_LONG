/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:58:11 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/02 15:11:03 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "./Libft/libft.h"
#include <fcntl.h> //open();
#include <unistd.h> //close(); read(); write();
#include <stdlib.h> // malloc(); free(); exit();
#include <stdio.h> //perror();
#include <string.h> //strerror();

typedef	struct s_map
{
	char	**map;
	char	**map_copy;
}			t_map;

int		error_main(int argc, char **argv);
int		check_filename(char *s);
int		verify_file(char *s);
int		check_valid_chars(int fd);
char	*ft_strdup_modified(char *s1);
char	*ft_strjoin_modified(char *s1, char *s2);
size_t	ft_strlen_modified(char *s);
char	*file_to_string(int fd);

#endif