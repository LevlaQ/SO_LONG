/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:54:38 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/09 11:16:31 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_main(int argc, char **argv, t_map **st)
{
	if (argc != 2)
		return (p_error("Error :Wrong argument count\n"), 0);
	if (!check_filename(argv[1]))
		return (p_error("Error :Wrong file extension\n"), 0);
	if (!(verify_file(argv[1])))
		return (p_error("Error :No file or no proper permissions\n"), 0);
	if (!(check_map_chars(argv[1])))
		return (p_error("Error :Invalid chars in map/ malloc fail\n"), 0);
	if (!(check_map_elements(argv[1])))
		return (p_error("Error :Must have 1P1E & C≥1/ malloc fail\n"), 0);
	if (!(file_to_string_matrix(argv[1], st)))
		return (p_error("Error : ft_split failed\n"), 0);
	if (!(validate_map_shape(st)))
		return (p_error("Error: Map is not rectangle\n"), 0);
	if (!(validate_walls(st)))
		return (p_error("Error: Map is not enclosed with walls\n"), 0);
	if (!(player_can_escape(st)))
		return (p_error("Error: Player escape impossible/ C left\n"), 0);
	return (1);
}

//Leak ihtimali!!!
int	check_filename(char *s)
{
	int		i;
	char	*no_exten;
	
	i = ft_strlen(s); //Döndürdüğü sayıyı direkt indekse alsam \0'dan başlarım olmaz
	if (s[i - 1] != 'r')
		return (0);
	if (s[i - 2] != 'e')
		return (0);
	if (s[i - 3] != 'b')
		return (0);
	if (s[i - 4] != '.')
		return (0);
	no_exten = ft_substr(s, 0, i - 4); //No exten malloc ile açıldı //TODO search file extensions
	if (ft_strchr(no_exten, '.') != NULL)
		return (free(no_exten), 0);
	return (free(no_exten), 1);
}

//Eğer bu fonksiyon doğru ise hemen karakter kontrollerine girsin
int	verify_file(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY); //2D diziye alınca close() etmeyi unutma!!!!
	if (fd == -1)
		return (0);
	else
		close(fd);
	return (1);
}
