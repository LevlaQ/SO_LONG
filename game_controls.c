/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:01:44 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/14 03:06:39 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	process_input(t_map *map)
{
	mlx_key_hook(map->mlx->mlx_window, keyhook, map);
	mlx_hook(map->mlx->mlx_window, 17, 0, exit_the_program, map);
}

int	keyhook(int keycode, t_map *map)
{
	if (keycode == 97 || keycode == 65361)
	{
		move_the_player(map, map->p_y, map->p_x - 1);
		return (render_tiles(map, 0, 0), 1);
	}
	if (keycode == 100 || keycode == 65363)
	{
		move_the_player(map, map->p_y, map->p_x + 1);
		return (render_tiles(map, 0, 0), 1);
	}
	if (keycode == 119 || keycode == 65362)
	{
		move_the_player(map, map->p_y - 1, map->p_x);
		return (render_tiles(map, 0, 0), 1);
	}
	if (keycode == 115 || keycode == 65364)
	{
		move_the_player(map, map->p_y + 1, map->p_x);
		return (render_tiles(map, 0, 0), 1);
	}
	if (keycode == 65307)
		exit_the_program(map);
}

/*
	Updates the player's position by moving to the specified
	(y, x) coordinates and adjusting the game state:
	it decreases the coin count when a coin is collected,
	and if the exit is reached with no remaining coins,
	it triggers a win state (printing a victory message);
	if coins are still left, it marks the move accordingly.
	The function first aborts any further movement if a win marker
	('W') is already present, ensuring that no moves are processed after winning.
*/
void	move_the_player(t_map *map, int y, int x)
{
	map->behind = '0';
	if (find_the_char(map, map->map, 'W'))
		return ;
	else if (map->map[y][x] == '0' || map->map[y][x] == 'C')
	{
		if (map->map[y][x] == 'C')
			map->c_count--;
		if (map->map[map->p_y][map->p_x] == 'A')
		{
			map->behind = 'E';
			move_one_tile_ahead(map, y, x, 'P');
		}
		else
			move_one_tile_ahead(map, y, x, 'P');
	}
	else if (map->map[y][x] == 'E' && map->c_count == 0)
	{
		move_one_tile_ahead(map, y, x, 'W');
		printf("\nYOU WON!\n");
	}
	else if (map->map[y][x] == 'E' && map->c_count != 0)
		move_one_tile_ahead(map, y, x, 'A');
}

/*
	Moves the player to the new (y, x) position
	and updates the game state accordingly.
	It sets the new tile with the given character,
	restores the previous tile using 'behind',
	increments the move counter, updates the player's coordinates,
	and prints the updated move count. 
*/
void	move_one_tile_ahead(t_map *map, int y, int x, char new_position)
{
	map->map[y][x] = new_position;
	map->map[map->p_y][map->p_x] = map->behind;
	map->p_moves++;
	map->p_x = x;
	map->p_y = y;
	ft_printf("%d\r", map->p_moves);
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
