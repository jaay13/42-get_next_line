/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoch <jakoch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 11:50:52 by jakoch            #+#    #+#             */
/*   Updated: 2026/05/31 16:54:26 by jakoch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <fcntl.h> // open
#include <unistd.h> // read, close
#include <stdio.h> // printf
#include <stdint.h> // SIZE_MAX
#include <stdlib.h> // malloc, free

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char *get_next_line(int fd);

/* ---------------	UTILS	--------------- */
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
#endif