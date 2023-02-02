/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:02:08 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/02/02 13:08:47 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
// needed for main:
#include <stdio.h>
#include <fcntl.h>

// finds the first line ending in \n from buffer
// this is the line for get_next_line to return
char	*next_line(char *a)
{
	int		i;
	char	*buf;

	if (!a || !a[0])
		return (NULL);
	i = 0;
	while (a[i] && a[i] != '\n')
		i++;
	if (a[i] == '\n')
		i++;
	buf = (char *)malloc((sizeof(char) * i) + 1);
	if (!buf)
		return (NULL);
	i = 0;
	while (a[i] && a[i] != '\n')
	{
		buf[i] = a[i];
		i++;
	}
	if (a[i] == '\n')
		buf[i++] = '\n';
	buf[i] = '\0';
	return (buf);
}

// finds the end of the line we just returned in the buffer
// moves it to the end of new buffer
// changes the \n before it to '\0', so our new buffer does not contain it
// this offsets our buffer, the buffer now starts
// at the next line to be printed
char	*offset(char *a)
{
	char	*buf;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (a[i] && a[i] != '\n')
		i++;
	if (a[i] == '\0')
	{
		free(a);
		return (NULL);
	}
	if (a[i] == '\n')
		i++;
	buf = (char *)malloc(ft_strlen(a) - i + 1);
	while (a[i + x])
	{
		buf[x] = a[i + x];
		x++;
	}
	buf[x] = '\0';
	free(a);
	return (buf);
}

// static buffer str starts at the next line to be printed
// we use strchr to find if there is a \n in the buffer
// if theres not, we read from the file into the buffer
// if \n is present, this is the line to print
// next_line then gets the first line ending in '\n' from the static buffer
// we return this line
// then we offset the static buffer by the line we just returned
char	*get_next_line(int fd)
{
	static char		*str;
	char			*buf;
	char			*tmp;
	int				i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!buf)
		return (NULL);
	i = 1;
	while (!(ft_strchr(str, '\n')) && i != 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[i] = '\0';
		tmp = ft_strjoin(str, buf);
		free(str);
		str = tmp;
	}
	free(buf);
	buf = next_line(str);
	str = offset(str);
	return (buf);
}

int	main(int argc, char *argv[])
{
	char	*line;
	int		fd;

	if (argc < 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file");
		return (1);
	}
	line = get_next_line(fd); 
	while (line != NULL) 
	{
		printf("%s", line);
		free(line); 
		line = get_next_line(fd); 
	}
	close (fd);
	return (0);
}
