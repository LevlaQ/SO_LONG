/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:58:11 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/14 03:06:49 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./Libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_tile
{
	void	*floor;
	void	*wall;
	void	*player;
	void	*collect;
	void	*exit;
	void	*win;
	void	*over;
}			t_tile;

typedef struct s_minx
{
	void	*mlx_ptr;
	void	*mlx_window;
}			t_minx;

typedef struct s_map
{
	char	**map;
	char	**map_copy;
	char	behind;
	int		m_width;
	int		m_height;
	int		p_y;
	int		p_x;
	int		c_count;
	int		p_moves;
	t_tile	*tiles;
	t_minx	*mlx;
}			t_map;

char	*ft_strdup_modified(char *s1);
char	*ft_strjoin_modified(char *s1, char *s2);
char	*file_to_string(char *s);
void	free_2d_arr(char **strings);
void	free_maps(t_map *st);
void	p_error(char *message);
void	print_error_and_exit(char *s, int error_no, int exit_no);
int		error_main(int argc, char **argv, t_map *st);
int		check_filename(char *s);
int		verify_file(char *s);
int		check_xpm_files(void);
size_t	ft_strlen_modified(char *s);
int		check_map_chars(char *s);
int		check_map_elements(char *s);
int		check_empty_lines_in_map(char *s);
int		file_to_string_matrix(char *s, t_map *st);
int		validate_map_shape(t_map *st);
int		validate_walls(t_map *st);
void	count_the_coins(t_map *st, char *s);
int		find_the_char(t_map *st, char **map, char c);
void	flood_exit(t_map *st, int y, int x);
int		player_can_escape(t_map *st);
void	start_and_exit_game(t_map *map);
void	pointer_to_xpm(t_map *map);
void	measure_map(t_map *map);
void	render_tiles(t_map *map, int y, int x);
void	put_image_to_window(t_map *map, int x, int y, void *img_ptr);
void	*put_xpm_file_to_image(t_map *map, char *filepath);
void	process_input(t_map *map);
int		keyhook(int keycode, t_map *map);
void	move_the_player(t_map *map, int y, int x);
void	move_one_tile_ahead(t_map *map, int y, int x, char new_position);
int		exit_the_program(t_map *st);

#endif