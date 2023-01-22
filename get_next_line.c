/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:02:08 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/01/22 20:45:55 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
// needed for main:
#include <stdio.h>
#include <fcntl.h>

int	get_char(int fd)
{
	unsigned char	c;
	int				i;

	i = read(fd, &c, 1);
	if (i == 1)
		return (c);
	else
		return (-1);
}

// TODO:
// recode this to use a static variable to keep track
// of the file descriptor in between function calls
// 
// store the number of bytes read in previous call
// use this value to continue reading on next call

char	*get_next_line(int fd)
{
	int		i;
	char	c;
	char	*buf;

	i = 0;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[i] = '\0';
	c = get_char(fd);
	while (c != -1)
	{
		if (c == '\n')
		{
			buf[i++] = c;
			break ;
		}
		buf[i++] = c;
		c = get_char(fd);
	}
	buf[i] = '\0';
	if (c == -1 && i == 0)
		return (NULL);
	return (buf);
}

int	main(int argc, char* argv[]) 
{
	char* line;
	if (argc < 2) {
		printf("Usage: %s <file>\n", argv[0]);
		return 1;
	}
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file");
		return 1;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close (fd);
	return (0);
}
