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

int is_end(char *str)		//0 - '\0', 1 - '\n', 2 - no end (\0 при s[BUFF_SIZE]), -1 - ошибка
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (i < BUFFER_SIZE)
	{
		if (str[i] == '\0')
		{
			return (0);
		}
		else if (str[i] == '\n')
		{
			str[i] = '\0';
			return (1);
		}
		i++;
	}
	return (2);
}

int get_next_line(int fd, char **line)
{
	char	*buff;
	int 	checkbuf;
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
		checkbuf = is_end(buff); // -1 - ошибка чтения, 0 - символов меньше BUFF_SIZE, 1 - найден \n, 2 - символов BUFF_SIZE (продолжение цикла)
		res = write_to_res(buff, res); // добавление buff в res (NULL - ошибка)
		if (res == NULL)
			checkbuf = -1;
		printf("cb:%d - buff:%s\n", checkbuf, buff);
	}
	*line = res;
	free(buff);
	return (checkbuf);
}
