/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:37:16 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/11 14:29:27 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	start_and_exit_game(t_map *map)
{
	map->mlx->mlx_ptr = mlx_init();
	if(!(map->mlx->mlx_ptr))
		print_error_and_exit("Cannot connect X server", ENOMEM, EXIT_FAILURE); //TODO Doğru bir error no mu kontrol et!!
	pointer_to_xpm(map);
	measure_map(map);
	map->mlx->mlx_window = mlx_new_window(map->mlx->mlx_ptr, map->m_width,\
		map->m_height, "so_long");
	if(!(map->mlx->mlx_window))
	{
		mlx_destroy_display(map->mlx->mlx_ptr); //Eğer window fail olursa mlx_init içindeki display struc'tı serbest bırakılmalı
		free(map->mlx->mlx_ptr); //Pointer'ın kendisi serbest bırakılmalı
		print_error_and_exit("Cannot open window", ENOMEM, EXIT_FAILURE);
	}
	render_tiles(map, 0, 0);
	
	
	
	mlx_loop(map->mlx->mlx_ptr); //TODO ne zaman nerede nasıl niçin neden 
	//mlx_key_hook();//TODO ne zaman nerede nasıl niçin neden 
}

void	pointer_to_xpm(t_map *map)
{
	char	*path;
	int		img_h;
	int		img_w;

	path = "./xpms/0.xpm";
	map->tiles->floor = mlx_xpm_file_to_image(map->mlx->mlx_ptr, path, &img_h,\
		&img_w); //TODO xpm uzunluğunu genişliğini geri döndürüyor
	path = "./xpms/1.xpm";
	map->tiles->wall = mlx_xpm_file_to_image(map->mlx->mlx_ptr, path, &img_h,\
		&img_w); //TODO pointer fail durumu exit kodları eklenecek
	path = "./xpms/collectible.xpm";
	map->tiles->collect = mlx_xpm_file_to_image(map->mlx->mlx_ptr, path, &img_h,\
		&img_w);
	path = "./xpms/player.xpm";
	map->tiles->player = mlx_xpm_file_to_image(map->mlx->mlx_ptr, path, &img_h,\
		&img_w);
	path = "./xpms/exit.xpm";
	map->tiles->exit = mlx_xpm_file_to_image(map->mlx->mlx_ptr, path, &img_h,\
		&img_w);
}

void	measure_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while(map->map[y])
		y++;
	while(map->map[0][x])
		x++;
	map->m_height = y;
	map->m_width = x;
}

/*
	Verilen pozisyonlardan itibaren "fayansları" ekrana dizmeye başlıyorum
*/
void	render_tiles(t_map *map, int y, int x)
{
	while(map->map[y])
	{
		x = 0;
		while(map->map[y][x])
		{
			if(map->map[y][x] == '1')
				mlx_put_image_to_window(map->mlx->mlx_ptr,\
					map->mlx->mlx_window, map->tiles->wall, x * 64, y * 64);
			if(map->map[y][x] == '0')
				mlx_put_image_to_window(map->mlx->mlx_ptr,\
					map->mlx->mlx_window, map->tiles->floor, x * 64, y * 64);
			if(map->map[y][x] == 'C')
				mlx_put_image_to_window(map->mlx->mlx_ptr,\
					map->mlx->mlx_window, map->tiles->collect, x * 64, y * 64);
			if(map->map[y][x] == 'E')
				mlx_put_image_to_window(map->mlx->mlx_ptr,\
					map->mlx->mlx_window, map->tiles->exit, x * 64, y * 64);
			if(map->map[y][x] == 'P')
				mlx_put_image_to_window(map->mlx->mlx_ptr,\
					map->mlx->mlx_window, map->tiles->player, x * 64, y * 64);
			x++;
		}
		y++;
	}
}
