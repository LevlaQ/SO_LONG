/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:22:11 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/09 11:09:54 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_2d_arr(char **strings)
{
	size_t	i;

	if (!strings)
		return ;
	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

void	free_maps(t_map **st)
{
	free_2d_arr((*st)->map);
	free_2d_arr((*st)->map_copy);
}

void	p_error(char *message)
{
	write(2, message, ft_strlen(message));
}