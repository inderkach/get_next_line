/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdanny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:57:30 by fdanny            #+#    #+#             */
/*   Updated: 2021/06/25 15:57:32 by fdanny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i) != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	ptr;

	if (s1 == NULL)
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

int is_end(char *str)		//1 - '\0', 2 - '\n', 0 - no end
{
	size_t	i;

	i = 0;
	while (i <= BUFFER_SIZE)
	{
		if (str[i] == '\0')
		{
			return (1);
		}
		else if (str[i] == '\n')
		{
			str[i] = '\0';
			return (2);
		}
		i++;
		write(1, "1", 1);
	}
	return (0);
}

int get_next_line(int fd, char **line)
{
	char	*buff;
	int 	ret;
	char	check_read;
	char	*res;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 ||
		(buff = malloc((BUFFER_SIZE + 1) * sizeof(char))) == NULL)
		return (-1);
	buff[BUFFER_SIZE] = '\0';
	
	res = malloc(sizeof(char));
	if (res == NULL)
	{
		free(buff);
		return (-1);
	}
	*res = '\0';
	ret = 2;
	while (ret != 0 && ret != 1)
	{
		check_read = read(fd, buff, BUFFER_SIZE);
		if (check_read == -1)
		{
			free(buff);
			free(res);
			return (-1);
		}
		ret = is_end(buff);
		res = ft_strjoin(buff, res);
		if (res == NULL)
		{
			free(buff);
			return (-1);
		}
	}
	*line = res;
	free(buff);
	return (ret);
}
