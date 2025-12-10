/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elarue <elarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:46:21 by enzolarue         #+#    #+#             */
/*   Updated: 2025/12/10 11:07:53 by elarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *buffer, char **stash)
{
	free(buffer);
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

char	*read_and_update_stash(int fd, char *stash)
{
	char	*buf;
	char	*tmp;
	ssize_t	read_bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (ft_free(buf, &stash));
	read_bytes = read(fd, buf, BUFFER_SIZE);
	if (read_bytes > 0)
	{
		buf[read_bytes] = '\0';
		tmp = ft_strjoin(stash, buf);
		free(stash);
		free(buf);
		return (tmp);
	}
	if (read_bytes == -1)
		return (ft_free(buf, &stash));
	free(buf);
	return (stash);
}

char	*extract_line_from_stash(char *stash)
{
	char	*after_line;
	size_t	len;

	if (!stash)
		return (NULL);
	after_line = ft_strchr(stash, '\n');
	if (!after_line)
		return (ft_strdup(stash));
	len = ft_strlen(stash) - ft_strlen(after_line) + 1;
	return (ft_substr(stash, 0, len));
}

char	*update_stash_after_extraction(char *stash)
{
	char	*after_line;
	char	*new_stash;

	if (!stash)
		return (NULL);
	after_line = ft_strchr(stash, '\n');
	if (!after_line)
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(after_line + 1);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	if (!new_stash[0])
	{
		free(new_stash);
		free(stash);
		return (NULL);
	}
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*old_stash;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	while (!stash || !ft_strchr(stash, '\n'))
	{
		old_stash = stash;
		stash = read_and_update_stash(fd, stash);
		if (!stash)
			return (NULL);
		if (stash == old_stash && stash && !ft_strchr(stash, '\n'))
			break ;
	}
	if (!stash || !stash[0])
	{
		stash = NULL;
		return (free(stash), NULL);
	}
	line = extract_line_from_stash(stash);
	if (!line)
		return (ft_free(line, &stash));
	stash = update_stash_after_extraction(stash);
	return (line);
}
