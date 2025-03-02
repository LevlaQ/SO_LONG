/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:45:39 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/02 12:25:19 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	if(!error_main(argc, argv))
		return (0);
	else
		ft_printf("All is well");
	return (1);
	// if (argc > 0)
	// 	printf("\n");
	// int fd = open(argv[1], O_RDONLY);
	// char *s1 = get_next_line(fd);
	// char *s2 = get_next_line(fd);
	// char *s3 = get_next_line(fd);
	// char *s4 = get_next_line(fd);
	// ft_printf("%s", s1);
	// ft_printf("%s", s2);
	// ft_printf("%s", s3);
	// ft_printf("%s", s4);

	//close (fd);
}