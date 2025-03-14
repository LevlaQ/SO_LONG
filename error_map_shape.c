/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map_shape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:16:07 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/14 03:06:01 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	file_to_string_matrix(char *s, t_map *st)
{
	char	*joined;

	joined = file_to_string(s);
	st->map = ft_split(joined, '\n');
	if (st->map == NULL)
		return (0);
	st->map_copy = ft_split(joined, '\n');
	if (st->map_copy == NULL)
		return (free(joined), 0);
	return (free(joined), 1);
}

/*
	Ensures all rows in 'st->map' have the same length as the first row.
	If any row length differs, returns 0 and frees the maps;
	otherwise returns 1.
*/
int	validate_map_shape(t_map *st)
{
	size_t	length;
	int		y;

	length = ft_strlen(st->map[0]);
	y = 0;
	while (st->map[y])
	{
		if (length != ft_strlen(st->map[y]))
			return (free_maps(st), 0);
		y++;
	}
	return (1);
}

/*
	Verifies that the map in 'st' is fully enclosed by walls:
	Each row must start and end with '1'.
	The first and last rows must be composed entirely of '1'.
	Returns 0 (and frees allocated memory) if any check fails,
	otherwise returns 1. 
*/
int	validate_walls(t_map *st)
{
	size_t	length;
	int		y;
	int		x;

	length = ft_strlen(st->map[0]);
	y = 0;
	x = 0;
	while (st->map[y])
	{
		if (!((st->map[y][0] == '1') && (st->map[y][length - 1] == '1')))
			return (free_2d_arr(st->map), free_2d_arr(st->map_copy), 0);
		y++;
	}
	while (st->map[0][x])
	{
		if (st->map[0][x] != '1')
			return (free_maps(st), 0);
		if (st->map[y - 1][x] != '1')
			return (free_maps(st), 0);
		x++;
	}
	return (1);
}

int	player_can_escape(t_map *st)
{
	find_the_char(st, st->map_copy, 'P');
	flood_exit(st, st->p_y, st->p_x);
	if (find_the_char(st, st->map_copy, 'E'))
		return (free_maps(st), 0);
	if (find_the_char(st, st->map_copy, 'C'))
		return (free_maps(st), 0);
	return (1);
}

void	flood_exit(t_map *st, int y, int x)
{
	char	new;
	char	wall;

	new = 'F';
	wall = '1';
	if (st->map_copy[y][x] == new
		|| st->map_copy[y][x] == wall)
		return ;
	else
	{
		st->map_copy[y][x] = new;
		flood_exit(st, y + 1, x);
		flood_exit(st, y - 1, x);
		flood_exit(st, y, x + 1);
		flood_exit(st, y, x - 1);
	}
}
