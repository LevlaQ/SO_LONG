/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:21:06 by gyildiz           #+#    #+#             */
/*   Updated: 2024/12/22 15:04:11 by gyildiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	i;
	char	*substr;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (start + len > slen)
		len = slen - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strdup(char *s1)
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
	return (dub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	st1;
	size_t	st2;
	size_t	i;
	char	*joined;

	if (!s1)
		return (ft_strdup(s2));
	st1 = ft_strlen(s1);
	st2 = ft_strlen(s2);
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
	return (joined);
}

int	find_the_nl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if ((char)c == s[i])
			return (1);
		else
			i++;
	}
	if ((char)c == s[i])
		return (1);
	return (0);
}

size_t	ft_strlen(char *s)
{
	size_t	a;

	if (!s)
		return (0);
	a = 0;
	while (s[a] != 0)
		a++;
	return (a);
}
