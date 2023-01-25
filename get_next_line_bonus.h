/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:02:28 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/01/25 19:52:07 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 255
# endif

char	*get_next_line(int fd);

int		ft_strlen(char *str);

char	*ft_strdup(char *src);

char	*ft_strcat(char *dest, char *src);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strchr(const char *src, int c);

#endif