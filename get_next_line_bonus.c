/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoch <jakoch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 11:50:21 by jakoch            #+#    #+#             */
/*   Updated: 2026/06/02 15:47:36 by jakoch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_next_line(int fd, char *stash);
static char	*append_buf(char *stash, char *buf);
static char	*get_output_from(char *stash);
static char	*clean_written_from(char *stash);

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_calloc(1, 1);
	if (!ft_strchr(stash[fd], '\n'))
		stash[fd] = read_next_line(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_output_from(stash[fd]);
	stash[fd] = clean_written_from(stash[fd]);
	return (line);
}

static char	*read_next_line(int fd, char *stash)
{
	char	*buf;
	int		bytes_read;

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
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen_c(stash, '\0');
	len2 = ft_strlen_c(buf, '\0');
	new_stash = malloc(len1 + len2 + 1);
	if (!new_stash)
		return (NULL);
	ft_strlcpy(new_stash, stash, len1 + 1);
	ft_strlcpy(new_stash + len1, buf, len2 + 1);
	free(stash);
	return (new_stash);
}

static char	*get_output_from(char *stash)
{
	int	len;

	if (!stash[0])
		return (NULL);
	len = ft_strlen_c(stash, '\n');
	return (ft_substr(stash, 0, len));
}

static char	*clean_written_from(char *stash)
{
	char	*leftover;
	size_t	len;
	size_t	total_len;

	len = ft_strlen_c(stash, '\n');
	total_len = ft_strlen_c(stash, '\0');
	if (!stash[len])
		return (free(stash), NULL);
	leftover = ft_substr(stash, len, total_len - len);
	free(stash);
	return (leftover);
}
