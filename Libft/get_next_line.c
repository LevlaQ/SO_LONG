/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:21:10 by gyildiz           #+#    #+#             */
/*   Updated: 2025/03/02 12:20:31 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*refresh_the_stat(char	*stat)
{
	size_t	cnt_nl;
	size_t	stat_len;
	char	*refreshed;

	cnt_nl = 0;
	stat_len = ft_strlen_m(stat);
	while (*(stat + cnt_nl) != '\n' && *(stat + cnt_nl) != '\0')
	{
		cnt_nl++;
	}
	if (*(stat + cnt_nl) == '\0')
	{
		free (stat);
		return (NULL);
	}
	else
		refreshed = ft_substr_m(stat, (cnt_nl + 1), (stat_len - (cnt_nl + 1)));
	if (!refreshed)
		return (NULL);
	free (stat);
	return (refreshed);
}

static char	*extract_line(char *stat)
{
	size_t	count_to_n;
	char	*line;

	if (!stat)
		return (NULL);
	count_to_n = 0;
	while (*(stat + count_to_n) != '\n' && *(stat + count_to_n) != '\0')
	{
		count_to_n++;
	}
	if (*(stat + count_to_n) == '\n')
		count_to_n++;
	line = ft_substr_m(stat, 0, (count_to_n));
	if (!line)
		return (NULL);
	return (line);
}

static char	*read_into_buffer_and_join_to_stat(int fd, char	*stat)
{
	char	*readed;
	int		return_of_read;

	readed = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	return_of_read = 1;
	while ((find_the_nl(stat, '\n') == 0) && (return_of_read != 0))
	{
		if (!readed)
			return (NULL);
		return_of_read = read(fd, readed, BUFFER_SIZE);
		if (return_of_read == -1)
		{
			if (stat)
				free(stat);
			return (free(readed), NULL);
		}
		readed[return_of_read] = '\0';
		stat = ft_strjoin_m(stat, readed);
		if (stat[0] == '\0' && return_of_read == 0)
		{
			return (free(readed), free(stat), NULL);
		}
	}
	return (free(readed), stat);
}

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*line_output;

	line_output = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stat = read_into_buffer_and_join_to_stat(fd, stat);
	if (!stat)
		return (NULL);
	line_output = extract_line(stat);
	if (!line_output)
		return (NULL);
	stat = refresh_the_stat(stat);
	return (line_output);
}
