/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoch <jakoch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 11:50:21 by jakoch            #+#    #+#             */
/*   Updated: 2026/05/30 15:41:35 by jakoch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_next_line(char *stash, int fd);
static char *append_buf(char *stash, char *buf);

char	*get_next_line(int fd)
{
	static char *stash;
	char *line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1);
	if (!ft_strchr(stash, '\n'))
		stash = read_next_line(stash, fd);
	if (!stash)
		return (free(stash), NULL);
	line = get_output_from(stash);
	stash = clean_written_from(stash);
	return (line);
}

static char *read_next_line(char *stash, int fd)
{
 char *buf;
 int  bytes_read;

 if (!stash)
	stash = ft_calloc(1, 1);
 buf = ft_calloc(BUFFER_SIZE + 1);
 if (!buf)
  return (NULL);
 bytes_read = 1;
 while (bytes_read > 0)
 {
  bytes_read = read(fd, buf, BUFFER_SIZE);
  if (bytes_read == -1)
   return (free(buf), NULL);
  buf[bytes_read] = '\0';
  stash = append_buf(stash, buf);
  if (ft_strchr(stash, '\n'))
   break ;
 }
 free (buf);
 return (stash);
}

static char *append_buf(char *stash, char *buf)
{
 char *new_stash;

 new_stash = ft_strjoin(stash, buf);
 free(stash);
 return (new_stash);
}