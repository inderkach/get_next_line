/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdanny <fdanny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:57:30 by fdanny            #+#    #+#             */
/*   Updated: 2021/07/01 12:11:42 by fdanny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i) != '\0' && *(s + i) != '\n')
		i++;
	return (i);
}

char	*write_to_res(char *sadd, char *s)
{
	char	*sres;
	size_t	i;
	size_t	j;

	sres = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(sadd) + 1));
	if (sres)
	{
		i = 0;
		while (s[i] != '\0' && s[i] != '\n')
		{	
			sres[i] = s[i];
			i++;
		}
		j = 0;
		while (sadd[j] != '\0' && sadd[j] != '\n')
		{
			sres[i] = sadd[j];
			i++;
			j++;
		}
	}
	free(s);
	return (sres);
}

int	is_end(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (i < BUFFER_SIZE)
	{
		if (str[i] == '\0')
			return (0);
		else if (str[i] == '\n')
		{
			str[i] = '\0';
			return (1);
		}
		i++;
	}
	return (2);
}

int	init_read(int fd, char **line, char *buff)
{
	int		checkbuf;
	char	check_read;
	char	*res;

	res = malloc(sizeof(char));
	if (res == NULL)
		return (-1);
	*res = '\0';
	checkbuf = 2;
	while (checkbuf == 2)
	{
		check_read = read(fd, buff, BUFFER_SIZE);
		if (check_read == -1)
		{
			free(buff);
			free(res);
			return (-1);
		}
		checkbuf = is_end(buff);
		res = write_to_res(buff, res);
		if (res == NULL)
			checkbuf = -1;
	}
	*line = res;
	return (checkbuf);
}

int	get_next_line(int fd, char **line)
{
	char	*buff;
	int		checkbuf;
	char	*res;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (-1);
	buff[BUFFER_SIZE] = '\0';
	checkbuf = init_read(fd, line, buff);
	free(buff);
	return (checkbuf);
}
