/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoch <jakoch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 11:50:21 by jakoch            #+#    #+#             */
/*   Updated: 2026/05/31 13:20:48 by jakoch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_next_line(int fd, char *stash);
static char	*append_buf(char *stash, char *buf);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, 1);
	if (!ft_strchr(stash, '\n'))
		stash = read_next_line(fd, stash);
	if (!stash)
		return (NULL);
	line = get_output_from(stash);
	stash = clean_written_from(stash);
	return (line);
}

static char	*read_next_line(int fd, char *stash)
{
	char	*buf;
	int		bytes_read;

	//if (!stash)
		//stash = ft_calloc(1, 1);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(stash), free(buf), NULL);
		buf[bytes_read] = '\0';
		stash = append_buf(stash, buf);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(buf);
	return (stash);
}

static char	*append_buf(char *stash, char *buf)
{
	char	*new_stash;

	new_stash = ft_strjoin(stash, buf);
	free(stash);
	return (new_stash);
}

static char	*get_output_from(char *stash)
{
	char *output;
	int len;

	output = stash;
	len = 0;
	if (!*output)
		return (NULL);
	while (output[len] && output[len] != '\n')
		len++;
	if (output[len] == '\n')
		len++;
	return (ft_substr(stash, 0, len));
}

static char *clean_written_from(char *stash)
{
	return(ft_substr());
}