/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:45:05 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/14 03:06:39 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	start_and_exit_game(t_map *map)
{
	map->mlx->mlx_ptr = mlx_init();
	if (!(map->mlx->mlx_ptr))
		print_error_and_exit("Cannot connect X server", ENOMEM, EXIT_FAILURE);
	pointer_to_xpm(map);
	measure_map(map);
	map->mlx->mlx_window = mlx_new_window(map->mlx->mlx_ptr, map->m_width, \
		map->m_height, "so_long");
	if (!(map->mlx->mlx_window))
	{
		mlx_destroy_display(map->mlx->mlx_ptr);
		free(map->mlx->mlx_ptr);
		print_error_and_exit("Cannot open window", ENOMEM, EXIT_FAILURE);
	}
	render_tiles(map, 0, 0);
	if (map->p_moves == 0)
		ft_printf("%d\r", 0);
	process_input(map);
	mlx_loop(map->mlx->mlx_ptr);
}
