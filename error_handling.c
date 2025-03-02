/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:54:38 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/02 15:32:05 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_main(int argc, char **argv)
{
	if (argc != 2)
		return (write(2, "Error (Wrong argument count)\n", 29), 0);
	if (!check_filename(argv[1]))
		return (write(2, "Error (Wrong file extension)\n", 29), 0);
	if (!(verify_file(argv[1])))
		return (write(2,"Error (No file or no proper permissions)\n", 41), 0);
	if (!(file_to_string(argv[1])))
		return (write(2,"Error (Malloc failure or empty file)\n", 37), 0);
	return (1);
}

int	check_filename(char *s)
{
	int	i;

	i = ft_strlen(s); //Döndürdüğü sayıyı direkt indekse alsam \0'dan başlarım olmaz
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
