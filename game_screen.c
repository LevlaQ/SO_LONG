/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:37:16 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/13 15:25:23 by gyildiz          ###   ########.fr       */
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
	if(map->P_moves == 0)
		ft_printf("%d\r", 0); //İlk sıfırı yazdırması için ekledim
	process_input(map);
	mlx_loop(map->mlx->mlx_ptr);
}

/*

	YUKARIYI AYRI DOSYAYA KOY

*/

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
			if(map->map[y][x] == 'A')
				put_image_to_window(map, x, y, map->tiles->over);
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

void	*put_xpm_file_to_image(t_map *map, char *filepath)
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


void	process_input(t_map *map)
{
	mlx_key_hook(map->mlx->mlx_window, keyhook, map);
	mlx_hook(map->mlx->mlx_window, 17, 0, exit_the_program, map);
}

/*
	ilgili tuş kodlarını aldıktan sonra ilgili fonksiyonları çağırarak hareket işlemini yaptırır
	her hareketten sonra  haritayı bir daha basar
*/
int	keyhook(int keycode, t_map *map)
{
	if(keycode == 97 || keycode == 65361)
	{
		move_the_player(map, map->P_y, map->P_x - 1);
		return(render_tiles(map, 0, 0), 1);
	}
	if(keycode == 100 || keycode == 65363) //Sütun bir artıyor (x + 1)
	{
		move_the_player(map, map->P_y, map->P_x + 1);
		return(render_tiles(map, 0, 0), 1);
	}
	if(keycode == 119 || keycode == 65362)//y - 1 satır azalıyot
	{
		move_the_player(map, map->P_y - 1, map->P_x);
		return(render_tiles(map, 0, 0), 1);
	}
	if(keycode == 115 || keycode == 65364) //satır artıyor y + 1
	{
		move_the_player(map, map->P_y + 1, map->P_x);
		return(render_tiles(map, 0, 0), 1);
	}
	if(keycode == 65307)
		exit_the_program(map);
}


/*

	Yeni player pozisyonu ataması yapmam lazım
	Topladığım coini azaltmam laım, 0 olacak sonunda!
	Gideceğim pozisyon duvar ise hiçbir şey yapmıyor, o yüzden koşulunu eklemedim
*/
void	move_the_player(t_map *map, int y, int x)
{
	map->behind = '0';
	if(find_the_char(map, map->map, 'W'))
		return ;
	else if(map->map[y][x] == '0' || map->map[y][x] == 'C') //Gideceğim pozisyonda çalı veya coin varsa
	{
		if(map->map[y][x] == 'C') //Eğer rastladığım şey coin ise
			map->C_count--;//Coin rastaladıkça bir azaltıyorum
		if(map->map[map->P_y][map->P_x] == 'A') //İleri ilerleyebiliyorum, ama eski pozisyonum A olacaksa yerine E koymalıyım
		{
			map->behind = 'E';
			move_one_tile_ahead(map, y, x, 'P');
		}
		else
			move_one_tile_ahead(map, y, x, 'P');
	}
	else if(map->map[y][x] == 'E' && map->C_count == 0) //Eğer gideceğim pozisyon exit ise ve hiç coin kalmamışsa
		move_one_tile_ahead(map, y, x, 'W');
	else if(map->map[y][x] == 'E' && map->C_count != 0)
		move_one_tile_ahead(map, y, x, 'A');
}

void	move_one_tile_ahead(t_map *map, int y, int x, char new_position)
{
	map->map[y][x] = new_position; //Gideceğim yere koyacağım görsel
	map->map[map->P_y][map->P_x] = map->behind;//Struct'tan aldığım player pozisyonuna yerleştireceğim görsel
	map->P_moves++; //Hamle yaptım bu yüzden hamle sayımı bir arttırıyorum
	map->P_x = x; //Struct içindeki oyuncu pozisyonumu güncelliyorum
	map->P_y = y;
	ft_printf("%d\r", map->P_moves); //Kaç hamle yapmışım yazıyorum
}

int	exit_the_program(t_map *st)
{	
	mlx_destroy_image(st->mlx->mlx_ptr, st->tiles->collect);
	mlx_destroy_image(st->mlx->mlx_ptr, st->tiles->exit);
	mlx_destroy_image(st->mlx->mlx_ptr, st->tiles->floor);
	mlx_destroy_image(st->mlx->mlx_ptr, st->tiles->player);
	mlx_destroy_image(st->mlx->mlx_ptr, st->tiles->wall);
	mlx_destroy_image(st->mlx->mlx_ptr, st->tiles->win);
	mlx_destroy_image(st->mlx->mlx_ptr, st->tiles->over);
	mlx_destroy_window(st->mlx->mlx_ptr, st->mlx->mlx_window);
	mlx_destroy_display(st->mlx->mlx_ptr);
	free(st->mlx->mlx_ptr);
	free(st->tiles);
	free(st->mlx);
	free_maps(st);
	free(st);
	exit(EXIT_SUCCESS);
}