/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:00:05 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/06 14:38:21 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strdup_modified(char *s1)
{
	size_t	str_size;
	size_t	chr_size;
	size_t	i;
	char	*dub;

	if (!s1)
		return (NULL);
	str_size = ft_strlen(s1) + 1;
	chr_size = sizeof(char);
	i = 0;
	dub = malloc(str_size * chr_size);
	if (dub == NULL)
		return (NULL);
	while (s1[i])
	{
		dub [i] = s1[i];
		i++;
	}
	dub[i] = '\0';
	free (s1);
	return (dub);
}

char	*ft_strjoin_modified(char *s1, char *s2)
{
	size_t	st1;
	size_t	st2;
	size_t	i;
	char	*joined;

	if (!s1)
		return (ft_strdup(s2));
	st1 = ft_strlen_modified(s1);
	st2 = ft_strlen_modified(s2);
	joined = (char *)malloc(sizeof(char) * (st1 + st2 + 1));
	if (!joined)
		return (NULL);
	i = -1;
	while (s1[++i])
		joined[i] = s1[i];
	i = 0;
	while (s2[i])
	{
		joined[st1 + i] = s2[i];
		i++;
	}
	joined[st1 + i] = '\0';
	free (s1);
	free (s2);
	return (joined);
}

size_t	ft_strlen_modified(char *s)
{
	size_t	a;

	if (!s)
		return (0);
	a = 0;
	while (s[a] != 0)
		a++;
	return (a);
}