/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:54:38 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/14 02:28:36 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_main(int argc, char **argv, t_map *st)
{
	if (argc != 2)
		return (p_error("Error :Wrong argument count\n"), 0);
	if (!check_filename(argv[1]))
		return (p_error("Error :Wrong file extension\n"), 0);
	if (!(verify_file(argv[1])))
		return (p_error("Error :No file or no proper permissions\n"), 0);
	if (!(check_xpm_files()))
		return (p_error("Error :No xpm files or no proper permissions\n"), 0);
	if (!(check_map_chars(argv[1])))
		return (p_error("Error :Invalid chars in map\n"), 0);
	if (!(check_map_elements(argv[1])))
		return (p_error("Error :Must have 1P1E & C≥1/ empty file\n"), 0);
	if (!(check_empty_lines_in_map(argv[1])))
		return (p_error("Error :Empty line in the map\n"), 0);
	if (!(file_to_string_matrix(argv[1], st)))
		return (p_error("Error : ft_split failed\n"), 0);
	if (!(validate_map_shape(st)))
		return (p_error("Error: Map is not rectangular\n"), 0);
	if (!(validate_walls(st)))
		return (p_error("Error: Map is not enclosed with walls\n"), 0);
	if (!(player_can_escape(st)))
		return (p_error("Error: Player escape impossible/ C left\n"), 0);
	count_the_coins(st, argv[1]);
	return (1);
}

int	check_filename(char *s)
{
	int		i;
	char	*no_exten;

	i = ft_strlen(s);
	if (s[i - 1] != 'r')
		return (0);
	if (s[i - 2] != 'e')
		return (0);
	if (s[i - 3] != 'b')
		return (0);
	if (s[i - 4] != '.')
		return (0);
	return (1);
}

int	verify_file(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (0);
	else
		close(fd);
	return (1);
}

int	check_xpm_files(void)
{
	if (!verify_file("./xpms/0.xpm"))
		return (0);
	if (!verify_file("./xpms/1.xpm"))
		return (0);
	if (!verify_file("./xpms/collectible.xpm"))
		return (0);
	if (!verify_file("./xpms/exit.xpm"))
		return (0);
	if (!verify_file("./xpms/player.xpm"))
		return (0);
	if (!verify_file("./xpms/win.xpm"))
		return (0);
	if (!verify_file("./xpms/A.xpm"))
		return (0);
	return (1);
}

/*
	This function reads the file's content into a single string,
	trimming trailing newline characters.
	It checks for consecutive newline characters in the map.
*/
int	check_empty_lines_in_map(char *s)
{
	int		i;
	int		len;
	char	*joined;

	joined = file_to_string(s);
	len = ft_strlen(joined);
	while (len > 0 && (joined[len - 1] == '\n'))
		len--;
	i = 0;
	while (i < len - 1)
	{
		if (joined[i] == '\n' && joined[i + 1] == '\n')
			return (free(joined), 0);
		i++;
	}
	return (free(joined), 1);
}
