/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:37:16 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/12 17:42:37 by gyildiz          ###   ########.fr       */
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
	render_tiles(map, 0, 0); //TODO Program başarılı sonlanana kadar her hareketten sonra tile render edilmeli
	// process_input(map);
	mlx_loop(map->mlx->mlx_ptr);
}

/*

	YUKARIYI AYRI DOSYAYA KOY

*/

void	pointer_to_xpm(t_map *map)
{
	map->tiles->wall = put_xpm_to_file(map, "./xpms/1.xpm");
	map->tiles->floor = put_xpm_to_file(map, "./xpms/0.xpm");
	map->tiles->collect = put_xpm_to_file(map, "./xpms/collectible.xpm");
	map->tiles->player = put_xpm_to_file(map, "./xpms/player.xpm");
	map->tiles->exit = put_xpm_to_file(map, "./xpms/exit.xpm");
	map->tiles->win = put_xpm_to_file(map, "./xpms/win.xpm");
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
	map->m_height = y * 64;
	map->m_width = x * 64;
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
				put_image_to_window(map, x, y, map->tiles->wall);
			if(map->map[y][x] == '0')
				put_image_to_window(map, x, y, map->tiles->floor);
			if(map->map[y][x] == 'C')
				put_image_to_window(map, x, y, map->tiles->collect);
			if(map->map[y][x] == 'E')
				put_image_to_window(map, x, y, map->tiles->exit);
			if(map->map[y][x] == 'P')
				put_image_to_window(map, x, y, map->tiles->player);
			if(map->map[y][x] == 'W')
				put_image_to_window(map, x, y, map->tiles->win);
			x++;
		}
		y++;
	}
}

void	put_image_to_window(t_map *map, int x, int y, void *img_ptr)
{
	mlx_put_image_to_window(map->mlx->mlx_ptr,\
		map->mlx->mlx_window, img_ptr, x * 64, y * 64);
}

void	*put_xpm_to_file(t_map *map, char *filepath)
{
	char	*tile;
	int		img_h;
	int		img_w;
	
	img_h = 64;
	img_w = 64;
	tile = mlx_xpm_file_to_image(map->mlx->mlx_ptr, filepath, &img_h,\
		&img_w);
	return (tile);
}
/*



BURADAN İTİBAREN HAREKETLER BAŞLIYOR



*/


// void	process_input(t_map *map)
// {
// 	mlx_key_hook(map->mlx->mlx_window, keyhook, map);
// 	mlx_hook(map->mlx->mlx_window, 17, 0, exit_the_program, map);
// }

// /*
// 	ilgili tuş kodlarını aldıktan sonra ilgili fonksiyonları çağırarak hareket işlemini yaptırır
// 	her hareketten sonra  haritayı bir daha basar
// */
// int		keyhook(int keycode, t_map *map)
// {
// 	if(keycode == 97 || keycode == 65361)
// 	{
// 		move_left(map);
// 		return(render_tiles(map, 0, 0), 1);
// 	}
// 	if(keycode == 100 || keycode == 65363)
// 	{
// 		move_right(map);
// 		return(render_tiles(map, 0, 0), 1);
// 	}
// 	if(keycode == 119 || keycode == 65362)
// 	{
// 		move_up(map);
// 		return(render_tiles(map, 0, 0), 1);
// 	}
// 	if(keycode == 115 || keycode == 65364)
// 	{
// 		move_down(map);
// 		return(render_tiles(map, 0, 0), 1);
// 	}
// 	if(keycode == 65307)
// 	{
// 		exit_the_program();
// 	}
// }


// void	move_left(t_map *map)
// {
	
// }

// void	move_right(t_map *map);

// void	move_up(t_map *map);

// void	move_down(t_map *map);

// void	exit_the_program(void);