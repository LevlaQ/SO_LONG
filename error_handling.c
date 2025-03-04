/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:54:38 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/04 17:29:29 by gyildiz          ###   ########.fr       */
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
		return (write(2, "Error: Map is not rectangle\n", 28), 0);
	if (!(validate_walls(st)))
		return (write(2, "Error: Map is not enclosed with walls\n", 38), 0);
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

// gnl okunacak satır olmadığında ne yapıyor? ->NULL döndürüyor
// gnl must work without leaks
// ft_strdup, ft_strjoin -> malloc without free
// Elde ettiğim joined malloc ile oluşturulmuş
char	*file_to_string(char *s)
{
	int		fd;
	char	*joined;
	char	*new;
	
	fd = open(s, O_RDONLY);
	joined = NULL;
	new = "\n"; // Döngüye girebilmek için nl ile başladım, ft_split ile sonradan kurtulacağım
	while(new)
	{
		if (!joined)
			joined = ft_strdup_modified(new);
		else
			joined = ft_strjoin_modified(joined, new);
		free (new);
		new = get_next_line(fd);
	}
	close(fd);
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

//GNL ile haritayı 2D array'e al struct içerisine al, "kopya" olabilmesi için malloc ile iki ayrı alan açılması lazım
//GNL satırı içeren char *ptr döndürüyor, malloc ile ayrılmış
//Joined'den split ile alırsam daha iyi gibi
//Split fail olduğunda 0 döndürecek
int	file_to_string_matrix(char *s, t_map **st)
{
	char *joined;

	joined = file_to_string(s);
	(*st) = ft_calloc(1, sizeof(t_map *)); //Pointer için de alan oluşturuyorum
	(*st)->map = ft_split(joined, '\n'); //SIGSEV //(*st)->map adresine erişilemiyor
	if ((*st)->map == NULL)
		return (0);
	(*st)->map_copy = ft_split(joined, '\n');
	if ((*st)->map_copy == NULL)
		return (0);
	return (1);
}

/*
	Argüman satırından dosya ismini alıp open() ile açacak
	Haritalar struct yapısına alındı, şimdi şekilleri kontrol edilecek
	y, y eksenini temsil ediyor
*/
int	validate_map_shape(t_map **st)
{
	size_t	length;
	int		y;

	length = ft_strlen((*st)->map[0]);
	y = 0;
	while((*st)->map[y])
	{
		if(length != ft_strlen((*st)->map[y])) //Eğer  birisi ilk ölçülen sütundan farklı bir uzunlukta ise
			return (free_2d_arr((*st)->map), free_2d_arr((*st)->map_copy), 0); //= döndür ama hata durumu freelemem lazım
		y++;
	}
	return (1);
}

/*
	Haritanın etrafı duvarlarla çevrili mi kontrolü
*/
int	validate_walls(t_map **st)
{
	size_t	length;
	int		y;
	int		x;

	length = ft_strlen((*st)->map[0]);
	y = 0;
	x = 0;
	while ((*st)->map[y])
	{
		if (!(((*st)->map[y][0] == '1') && ((*st)->map[y][length - 1] == '1'))) //Orta alanların duvar kontrolü, string'in iki ucunda 1 olmak zorunda, eğer durum bu değilse
			return (free_2d_arr((*st)->map), free_2d_arr((*st)->map_copy), 0); //Eğer durum bu değilse 0 döndür
		y++;
	}
	while ((*st)->map[0][x])
	{
		if((*st)->map[0][x] != '1')
			return (free_2d_arr((*st)->map), free_2d_arr((*st)->map_copy), 0); //Duvarlar boydan boya mı kontrolü
		if((*st)->map[y - 1][x] != '1')
			return (free_2d_arr((*st)->map), free_2d_arr((*st)->map_copy), 0);
		x++;
	}
	return (1);
	
}


