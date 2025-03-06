/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:54:38 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/06 18:20:34 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_main(int argc, char **argv, t_map **st)
{
	if (argc != 2)
		return (write(2, "Error :Wrong argument count\n", 28), 0);
	if (!check_filename(argv[1]))
		return (write(2, "Error :Wrong file extension\n", 28), 0);
	if (!(verify_file(argv[1])))
		return (write(2, "Error :No file or no proper permissions\n", 40), 0);
	if (!(check_map_chars(argv[1])))
		return (write(2, "Error :Invalid chars in map/ malloc fail\n", 42), 0); 
	if (!(check_map_elements(argv[1])))
		return (write(2, "Error :Must have 1P1E & C≥1/ malloc fail\n", 42), 0);
	if (!(file_to_string_matrix(argv[1], st)))
		return (write(2, "Error : ft_split failed\n", 24), 0);
	if (!(validate_map_shape(st)))
	{
		free_maps(st);
		return (write(2, "Error: Map is not rectangle\n", 28), 0);
	}
	if (!(validate_walls(st)))
	{
		free_maps(st);
		return (write(2, "Error: Map is not enclosed with walls\n", 38), 0);
	}
	if (!(player_can_escape(st)))
	{
		free_maps(st);
		return (write(2, "Error: Player escape impossible\n", 32), 0);
	}
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
	no_exten = ft_substr(s, 0, i - 4); //No exten malloc ile açıldı
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
