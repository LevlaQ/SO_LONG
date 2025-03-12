/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:01:44 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/12 13:55:57 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//int mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param)

void	process_input(t_map *map)
{
	mlx_key_hook(map->mlx->mlx_ptr, keyhook_a, map);
}

int		keyhook_a(int keycode, t_map *map)
{
	printf("%d\n", keycode);
}

