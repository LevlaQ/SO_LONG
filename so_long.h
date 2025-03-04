/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:58:11 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/04 14:25:06 by gyildiz          ###   ########.fr       */
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

char	*ft_strdup_modified(char *s1);
char	*ft_strjoin_modified(char *s1, char *s2);
char	*file_to_string(char *s);
void	free_2d_arr(char **strings);
int		error_main(int argc, char **argv, t_map **st);
int		check_filename(char *s);
int		verify_file(char *s);
size_t	ft_strlen_modified(char *s);
int		check_map_chars(char *s);
int		check_map_elements(char *s);
int		file_to_string_matrix(char *s, t_map **st);
int		validate_map_shape(t_map **st);
int		validate_walls(t_map **st);



#endif