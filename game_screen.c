/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:37:16 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/14 02:54:24 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	measure_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map->map[y])
		y++;
	while (map->map[0][x])
		x++;
	map->m_height = y * 64;
	map->m_width = x * 64;
}

/*
	Renders a 64x64 pixel image on the window
	by scaling the grid coordinates (x, y) by 64.
	Utilizes the MLX library to position the image
	at the computed pixel location.
*/
void	put_image_to_window(t_map *map, int x, int y, void *img_ptr)
{
	mlx_put_image_to_window(map->mlx->mlx_ptr, \
		map->mlx->mlx_window, img_ptr, x * 64, y * 64);
}

void	*put_xpm_file_to_image(t_map *map, char *filepath)
{
	char	*tile;
	int		img_h;
	int		img_w;

	img_h = 64;
	img_w = 64;
	tile = mlx_xpm_file_to_image(map->mlx->mlx_ptr, filepath, &img_h, \
		&img_w);
	return (tile);
}

void	pointer_to_xpm(t_map *map)
{
	map->tiles->wall = put_xpm_file_to_image(map, "./xpms/1.xpm");
	map->tiles->floor = put_xpm_file_to_image(map, "./xpms/0.xpm");
	map->tiles->collect = put_xpm_file_to_image(map, "./xpms/collectible.xpm");
	map->tiles->player = put_xpm_file_to_image(map, "./xpms/player.xpm");
	map->tiles->exit = put_xpm_file_to_image(map, "./xpms/exit.xpm");
	map->tiles->win = put_xpm_file_to_image(map, "./xpms/win.xpm");
	map->tiles->over = put_xpm_file_to_image(map, "./xpms/A.xpm");
}

/*
	Iterates over the entire 2D map array
	starting from the given (y, x) position,
	and renders each tile onto the window
	based on the character found (e.g., '1' for wall, '0' for floor, etc.).
*/
void	render_tiles(t_map *map, int y, int x)
{
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '1')
				put_image_to_window(map, x, y, map->tiles->wall);
			if (map->map[y][x] == '0')
				put_image_to_window(map, x, y, map->tiles->floor);
			if (map->map[y][x] == 'C')
				put_image_to_window(map, x, y, map->tiles->collect);
			if (map->map[y][x] == 'E')
				put_image_to_window(map, x, y, map->tiles->exit);
			if (map->map[y][x] == 'P')
				put_image_to_window(map, x, y, map->tiles->player);
			if (map->map[y][x] == 'W')
				put_image_to_window(map, x, y, map->tiles->win);
			if (map->map[y][x] == 'A')
				put_image_to_window(map, x, y, map->tiles->over);
			x++;
		}
		y++;
	}
}
