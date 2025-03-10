/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:58:11 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/10 14:14:36 by gyildiz          ###   ########.fr       */
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
	int		P_y;
	int		P_x;
	int		C_count;
	t_tile	*tiles;
	t_minx	*mlx;
	
}			t_map;

typedef	struct s_tile
{
	void	*floor;
	void	*wall;
	void	*player;
	void	*collect;
	void	*exit;
}			t_tile;

typedef	struct s_minx
{
	void	*mlx_ptr;
	void	*mlx_window;
}			t_minx;

char	*ft_strdup_modified(char *s1);
char	*ft_strjoin_modified(char *s1, char *s2);
char	*file_to_string(char *s);
void	free_2d_arr(char **strings);
void	free_maps(t_map **st);
void	p_error(char *message);
int		error_main(int argc, char **argv, t_map **st);
int		check_filename(char *s);
int		verify_file(char *s);
int		check_xpm_files(void);
size_t	ft_strlen_modified(char *s);
int		check_map_chars(char *s);
int		check_map_elements(char *s);
int		file_to_string_matrix(char *s, t_map **st);
int		validate_map_shape(t_map **st);
int		validate_walls(t_map **st);
int		find_the_char(t_map **st, char c);
void	flood_exit(t_map **st, int y, int x);
int		player_can_escape(t_map **st);
void	print_the_map(t_map **st); //Debug fonksiyonu
void	print_the_ori_map(t_map **st); //Debug fonksiyonu



#endif