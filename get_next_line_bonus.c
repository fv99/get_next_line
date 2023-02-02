/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:52:07 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/02/02 15:14:07 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
// this offsets our buffer so 
//the buffer now starts at the next line to be printed
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

char	*read_file(int fd, char *str, char *buf, char *tmp)
{
	int		i;

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
	return (str);
}

// for bonus modified static buffer
// so we have an array for out file descriptors
char	*get_next_line(int fd)
{
	static char		*str[BUFFER_SIZE] = {NULL};
	char			*tmp[BUFFER_SIZE];
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!buf)
		return (NULL);
	str[fd] = read_file(fd, str[fd], buf, tmp[fd]);
	free(buf);
	buf = next_line(str[fd]);
	str[fd] = offset(str[fd]);
	return (buf);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;

// 	fd1 = open("input1.txt", O_RDONLY);
// 	if (fd1 == -1)
// 	{
// 		perror("Failed to open fd1");
// 		return (1);
// 	}
// 	fd2 = open("input2.txt", O_RDONLY);
// 	if (fd2 == -1)
// 	{
// 		perror("Failed to open fd2");
// 		return (1);
// 	}
// 	fd3 = open("input3.txt", O_RDONLY);
// 	if (fd3 == -1)
// 	{
// 		perror("Failed to open fd3");
// 		return (1);
// 	}
// 	line = get_next_line(fd1);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd2);
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd3);
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd1);
// 	}
// 	close (fd1);
// 	close (fd2);
// 	close (fd3);
// 	return (0);
// }
