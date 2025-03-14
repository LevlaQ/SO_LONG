/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:15:01 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/14 10:16:38 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_the_map(t_map *st)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (st->map_copy[y] != NULL)
	{
		x = 0;
		while (st->map_copy[y][x] != '\0')
		{
			printf("%c", st->map_copy[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	print_the_ori_map(t_map *st)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (st->map[y] != NULL)
	{
		x = 0;
		while (st->map[y][x] != '\0')
		{
			printf("%c", st->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
