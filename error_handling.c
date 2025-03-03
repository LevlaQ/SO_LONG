/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:54:38 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/03 14:52:18 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_main(int argc, char **argv)
{
	if (argc != 2)
		return (write(2, "Error :Wrong argument count\n", 28), 0);
	if (!check_filename(argv[1]))
		return (write(2, "Error :Wrong file extension\n", 28), 0);
	if (!(verify_file(argv[1])))
		return (write(2,"Error :No file or no proper permissions\n", 40), 0);
	if (!(check_map_chars(argv[1])))
		return (write(2,"Error :Invalid chars in map / malloc fail\n", 42), 0);
	if (!(check_map_elements(argv[1])))
		return (write(2,"Error :Must have 1P1E & C≥1 / malloc fail\n", 42), 0);
	return (1);
}

//Leak ihtimali!!!
int	check_filename(char *s)
{
	int	i;
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
	if (ft_strchr(no_exten, '.') != NULL);
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
		close (fd);
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
		new = get_next_line(fd);
	}
	return (joined);
}

/*
	Haritanın içerisinde 1, 0, P, E, C, \n harici 
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
		if(ft_strchr(joined, 'P') != NULL)
			count_p++;
		if(ft_strchr(joined, 'E') != NULL)
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
	Argüman satırından dosya ismini alığ open() ile açacak
*/
int		validate_map_shape(char *s)
{
	int	fd;
}

//GNL ile haritayı 2D array'e al
char	**file_to_string_matrix(int fd)
{
	
}