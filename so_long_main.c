/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:45:39 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/06 21:11:22 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map_st;
	
	map_st = ft_calloc(1, sizeof(t_map *));
	if(!error_main(argc, argv, &map_st))
		return (free(map_st), 0);
	else
		ft_printf("All is well");
	return (1);
}