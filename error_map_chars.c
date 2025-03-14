/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:15:48 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/14 03:06:16 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	Reads the file specified by 's' line by line and
	concatenates everything into one string, then returns it.
	Starts with a newline in 'new' to initiate the read loop,
	appends each line to 'joined', and closes the file before returning.
*/
char	*file_to_string(char *s)
{
	int		fd;
	char	*joined;
	char	*new;

	fd = open(s, O_RDONLY);
	joined = NULL;
	new = ft_calloc(2, sizeof(char));
	new[0] = '\n';
	while (new)
	{
		if (!joined)
			joined = ft_strdup_modified(new);
		else
			joined = ft_strjoin_modified(joined, new);
		new = get_next_line(fd);
	}
	close(fd);
	return (joined);
}

int	check_map_chars(char *s)
{
	int		i;
	char	*joined;

	i = 0;
	joined = file_to_string(s);
	while (joined[i])
	{
		if (joined[i] != '1' && joined[i] != '0' && joined[i] != 'C' && \
			joined[i] != 'P' && joined[i] != 'E' && joined[i] != '\n')
			return (free(joined), 0);
		i ++;
	}
	return (free(joined), 1);
}

/*
	Checks if the map read from the file 's' contains at least one
	'C' and exactly one 'P' and one 'E'.
*/
int	check_map_elements(char *s)
{
	int		i;
	int		count_p;
	int		count_e;
	char	*joined;

	joined = file_to_string(s);
	if (ft_strchr(joined, 'C') == NULL)
		return (free(joined), 0);
	i = 0;
	count_p = 0;
	count_e = 0;
	while (joined[i])
	{
		if (joined[i] == 'P')
			count_p++;
		if (joined[i] == 'E')
			count_e++;
		i++;
	}
	if (count_p != 1)
		return (free(joined), 0);
	if (count_e != 1)
		return (free(joined), 0);
	return (free(joined), 1);
}

/*
	Searches through 'map' for the specified character 'c'.
	If 'c' is found and is 'P',the function saves its coordinates
	in the 't_map' structure 'st'. Returns 1 if the character is found,
	or 0 otherwise. 
*/
int	find_the_char(t_map *st, char **map, char c)
{
	int	y;
	int	x;

	y = 1;
	x = 1;
	while (map[y])
	{
		x = 1;
		while (map[y][x])
		{
			if (map[y][x] == c)
			{
				if (c == 'P')
				{
					st->p_y = y;
					st->p_x = x;
				}
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	count_the_coins(t_map *st, char *s)
{
	int		i;
	int		count_c;
	char	*joined;

	joined = file_to_string(s);
	i = 0;
	count_c = 0;
	while (joined[i])
	{
		if (joined[i] == 'C')
			count_c++;
		i++;
	}
	st->c_count = count_c;
	free(joined);
}
