/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdanny <fdanny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:57:15 by fdanny            #+#    #+#             */
/*   Updated: 2021/07/01 11:12:42 by fdanny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *to, char *from, size_t length)
{
	while (length != 0)
	{
		to[length] = from[length];
		length--;
	}
	*to = *from;
	return (to);
}

int	check_n(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	return (-1);
	while (s[i] != '\0')
	{
	if (s[i] == '\n')
	return (i);
	i++;
	}
	return (-1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i) != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	ptr;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	ptr = 0;
	joined = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (joined == 0)
		return (NULL);
	while (ptr < ft_strlen(s1))
	{
		*(joined + ptr) = *(s1 + ptr);
		ptr++;
	}
	ptr = 0;
	while (ptr < ft_strlen(s2))
	{
		*(joined + ft_strlen(s1) + ptr) = *(s2 + ptr);
		ptr++;
	}
	*(joined + ft_strlen(s1) + ft_strlen(s2)) = '\0';
	return (joined);
}

char	*alloc(char **res)
{
	if (*res == NULL)
	{
		*res = malloc(sizeof(char) * 1);
		if (*res != NULL)
			**res = '\0';
	}
	return (*res);
}