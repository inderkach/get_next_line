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

char	*to_line(char *s)
{
	char	*line;
	size_t	n_s;

	n_s = (size_t)check_n(s);
	line = malloc(sizeof(char) * n_s);
	line = ft_strcpy(line, s, n_s);
	line[n_s] = '\0';
	return (line);
}

char	*to_next_line(char *s)
{
	size_t	i;
	size_t	length;
	char	*new;

	i = (size_t)check_n(s) + 1;
	length = 0;
	while (s[i + length] != '\0')
		length++;
	new = malloc(sizeof(char) * (length + 1));
	new = ft_strcpy(new, (s + i), length + 1);
	free(s);
	return (new);
}

int	read_line(int fd, char *buff, char **res)
{
	int		reader;
	char	*newres;

	*res = alloc(res);
	
	if (*res != NULL)
	{
		reader = BUFFER_SIZE;
		while (reader == BUFFER_SIZE)
		{
			reader = read(fd, buff, BUFFER_SIZE);
			//printf("reader:%d\nbuffer:%s\n", reader, buff);
			buff[reader] = '\0';
			if (reader == -1)
				return (-1);
			newres = ft_strjoin(*res, buff);
			free(*res);
			*res = newres;
			if (check_n(buff) != -1)
				return (1);
		}
		return (0);
	}
	return (-1);
}

int	case_n(char **line, char **res)
{
	*line = to_line(*res);
	*res = to_next_line(*res);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*res;
	int			out;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (check_n(res) != -1)
		return (case_n(line, &res));
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (-1);
	out = read_line(fd, buff, &res);
	if (out == 0)
		*line = res;
	else if (out == 1)
		out = case_n(line, &res);
	free(buff);
	return (out);
}