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

char	*to_line(char *s, int *status)
{
	char	*line;
	size_t	n_s;

	if (s == NULL)
		return (NULL);
	if (check_n(s) != -1)
	{
		n_s = (size_t)check_n(s);
		*status = 1;
	}
	else
	{
		n_s = ft_strlen(s);
		*status = 0;
	}
	line = malloc(sizeof(char) * (n_s + 1));
	if (line == NULL)
		return (NULL);
	line = ft_strcpy(line, s, n_s);
	line[n_s] = '\0';
	return (line);
}

char	*to_next_line(char *s)
{
	size_t	i;
	size_t	length;
	char	*new;
//	printf("cn:%d", check_n(s));
	if ( s == NULL)
		return (NULL);
	if (check_n(s) != -1)
		i = (size_t)check_n(s) + 1;
	else
		i = ft_strlen(s);
	if (s[i] == '\0')
	{
		free(s);
		return (0);
	}
	length = ft_strlen(s + i);
	new = malloc(sizeof(char) * (length + 1));
	if (new == NULL)
		return (NULL);
	new = ft_strcpy(new, (s + i), length);
	//printf("\nfree p=%p\n", s);
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
//			printf("reader:%d\nbuffer:%s\n", reader, buff);
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
	int	status;

	*line = to_line(*res, &status);
	*res = to_next_line(*res);
	if (*line == NULL)
		return (-1);
	return (status);
}

int	get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*res;
	int			out;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	out = 1;
	if (check_n(res) == -1)
	{	
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return (-1);
		out = read_line(fd, buff, &res);
		free(buff);
	}
	if (out != -1)
		out = case_n(line, &res);
	return (out);
}