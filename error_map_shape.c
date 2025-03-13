/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map_shape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:16:07 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/13 13:08:13 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//GNL ile haritayı 2D array'e al struct içerisine al, "kopya" olabilmesi için malloc ile iki ayrı alan açılması lazım
//GNL satırı içeren char *ptr döndürüyor, malloc ile ayrılmış
//Joined'den split ile alırsam daha iyi gibi
//Split fail olduğunda 0 döndürecek
//Joined kullanılıp yeni alan oluşturuldu, join alanına gerek kalmadı
int	file_to_string_matrix(char *s, t_map *st)
{
	char *joined;

	joined = file_to_string(s);
	st->map = ft_split(joined, '\n'); //SIGSEV //(*st)->map adresine erişilemiyor
	if (st->map == NULL)
		return (0);
	st->map_copy = ft_split(joined, '\n');
	if (st->map_copy == NULL)
		return (free(joined), 0);
	return (free(joined), 1);
}

/*
	Argüman satırından dosya ismini alıp open() ile açacak
	Haritalar struct yapısına alındı, şimdi şekilleri kontrol edilecek
	y, y eksenini temsil ediyor
*/
int	validate_map_shape(t_map *st)
{
	size_t	length;
	int		y;

	length = ft_strlen(st->map[0]);
	y = 0;
	while(st->map[y])
	{
		if(length != ft_strlen(st->map[y])) //Eğer  birisi ilk ölçülen sütundan farklı bir uzunlukta ise
			return (free_maps(st), 0); //= döndür ama hata durumu freelemem lazım
		y++;
	}
	return (1);
}

/*
	Haritanın etrafı duvarlarla çevrili mi kontrolü
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
		if (!((st->map[y][0] == '1') && (st->map[y][length - 1] == '1'))) //Orta alanların duvar kontrolü, string'in iki ucunda 1 olmak zorunda, eğer durum bu değilse
			return (free_2d_arr(st->map), free_2d_arr(st->map_copy), 0); //Eğer durum bu değilse 0 döndür
		y++;
	}
	while (st->map[0][x])
	{
		if(st->map[0][x] != '1')
			return (free_maps(st), 0); //Duvarlar boydan boya mı kontrolü
		if(st->map[y - 1][x] != '1')
			return (free_maps(st), 0);
		x++;
	}
	return (1);
	
}

int	player_can_escape(t_map *st)
{
	find_the_char(st, st->map_copy, 'P');
	flood_exit(st, st->P_y, st->P_x);
	if (find_the_char(st, st->map_copy, 'E')) //Flood başarısız ise 'E' harfi bulunur.
		return (free_maps(st), 0);
	if (find_the_char(st, st->map_copy, 'C'))
		return (free_maps(st), 0);
	return (1);
}

/*
	SIGSEV yersem buradan yerim, fena yerim
	İlk elemandan geriye gitmeye çalışırsam segmentasyon yerim
	Harita net olarak duvarlarla kaplı, bunun kontrolü önceden 
	yapılmıştı, sınır için harita uzunluk genişlik hesabı yapmayayım
*/
void	flood_exit(t_map *st, int y, int x)
{
	char	new;
	char	wall;

	new = 'F';
	wall = '1';
	if(st->map_copy[y][x] == new
		|| st->map_copy[y][x] == wall) //Eğer harita sınırları dışına çıkmamışsam veya duvara rastlamışsam bir şey yapma
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