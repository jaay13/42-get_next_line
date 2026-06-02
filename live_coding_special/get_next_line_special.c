/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_special.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoch <jakoch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 11:50:21 by jakoch            #+#    #+#             */
/*   Updated: 2026/06/02 15:49:48 by jakoch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_special.h"

static char	*read_next_line(int fd, char *stash, char c);
static char	*append_buf(char *stash, char *buf);
static char	*get_output_from(char *stash, char c);
static char	*clean_written_from(char *stash, char c);

char	*get_next_line(int fd, char c)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, 1);
	if (!ft_strchr(stash, '\n'))
		stash = read_next_line(fd, stash, c);
	if (!stash)
		return (NULL);
	line = get_output_from(stash, c);
	stash = clean_written_from(stash, c);
	return (line);
}

static char	*read_next_line(int fd, char *stash, char c)
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
		if (ft_strchr(stash, c))
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

static char	*get_output_from(char *stash, char c)
{
	int		len;
	char	*output;
	char	*new_line;

	if (!stash[0])
		return (NULL);
	len = ft_strlen_c(stash, c);
	output = ft_substr(stash, 0, len);
	new_line = malloc(len + 2);
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, output, len + 1);
	new_line[len] = '\n';
	new_line[len + 1] = '\0';
	free(output);
	return (new_line);
}

static char	*clean_written_from(char *stash, char c)
{
	char	*leftover;
	size_t	len;
	size_t	total_len;

	len = ft_strlen_c(stash, c);
	total_len = ft_strlen_c(stash, '\0');
	if (!stash[len])
		return (free(stash), NULL);
	leftover = ft_substr(stash, len, total_len - len);
	free(stash);
	return (leftover);
}
