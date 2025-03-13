/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:15:48 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/13 23:52:31 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	Doyadaki haritayı tek bir string halinde alıyor
*/
char	*file_to_string(char *s)
{
	int		fd;
	char	*joined;
	char	*new;
	
	fd = open(s, O_RDONLY);
	joined = NULL;
	new = ft_calloc(2, sizeof(char)); //Calloc terminator ekledi 
	new[0] = '\n'; // Döngüye girebilmek için nl ile başladım, ft_split ile sonradan kurtulacağım
	while(new)
	{
		if (!joined)
			joined = ft_strdup_modified(new);
		else
			joined = ft_strjoin_modified(joined, new);
		new = get_next_line(fd);
	}
	close(fd); //Burada new ile alakalı bir sorunum var mem leak
	return (joined);
}

/*
	Haritanın içerisinde 1, 0, P, E, C, \n harici 
	s alıyor file_to_string fonksiyonu için
*/
int	check_map_chars(char *s)
{
	int		i;
	char	*joined;
	
	i = 0;
	joined = file_to_string(s);
	while (joined[i])
	{
		if (joined[i] != '1' && joined[i] != '0' && joined[i] != 'C' &&
			joined[i] != 'P' && joined[i] != 'E' && joined[i] != '\n')
			return (free(joined), 0);
		i ++;
	}
	return (free(joined), 1);
}
/*
	Haritanın içerisinde hiç C yoksa
	Haritanın içerisinde 1 den fazla P ve E varsa => 0
	Herşey yolunda ise 0 => 1
*/
int	check_map_elements(char *s)
{
	int		i;
	int		count_p;
	int		count_e;
	char	*joined;

	joined = file_to_string(s);
	if(ft_strchr(joined, 'C') == NULL)
		return(free(joined), 0);
	i = 0;
	count_p = 0;
	count_e = 0;
	while(joined[i])
	{
		if(joined[i] == 'P')
			count_p++;
		if(joined[i] == 'E')
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
	Bulmak istediğim karakterin, varsa eğer, koordinatlarını struct içerisine yazıyor
	Eğer floodfill başarılı bir şekilde çalışırsa benim elimde oyuncumun başlangıç pozisyonu olacak
	Aradığım karakteri bulursa 1, bulamazsa 0 döndürüyor
	
*/
int	find_the_char(t_map *st, char **map, char c)
{
	int	y;
	int	x;

	y = 1;
	x = 1;
	while(map[y]) //Initialize etmesem ft_calloc ile her şey baştan sıfırlandı
	{
		x = 1;
		while(map[y][x])
		{
			if(map[y][x] == c)
			{
				if(c = 'P') //Eğer aradığım karakter P ise konumunu struct'yaz
				{
					st->P_y = y;
					st->P_x = x;
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
	while(joined[i])
	{
		if(joined[i] == 'C')
			count_c++;
		i++;
	}
	st->C_count = count_c;
	free(joined);
}
