/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elarue <elarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:46:21 by enzolarue         #+#    #+#             */
/*   Updated: 2025/12/03 17:37:05 by elarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*read_and_update_storage(int fd, char *storage)
{
	char	*buf;
	char	*tmp;
	ssize_t	read_bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(storage), NULL);
	read_bytes = read(fd, buf, BUFFER_SIZE);
	if (read_bytes > 0)
	{
		buf[read_bytes] = '\0';
		tmp = ft_strjoin(storage, buf);
		free(storage);
		free(buf);
		return (tmp);
	}
	free(buf);
	if (read_bytes == -1)
		return (free(storage), NULL);
	return (storage);
}

char	*extract_line_from_storage(char *storage)
{
	char	*after_line;
	size_t	len;

	if (!storage)
		return (NULL);
	after_line = ft_strchr(storage, '\n');
	if (!after_line)
		return (ft_strdup(storage));
	len = (after_line - storage) + 1;
	return (ft_substr(storage, 0, len));
}

char	*update_storage_after_extraction(char *storage)
{
	char	*after_line;
	char	*new_storage;

	if (!storage)
		return (NULL);
	after_line = ft_strchr(storage, '\n');
	if (!after_line)
	{
		free(storage);
		return (NULL);
	}
	new_storage = ft_strdup(after_line + 1);
	if (!new_storage)
	{
		free(storage);
		return (NULL);
	}
	if (!new_storage[0])
	{
		free(new_storage);
		free(storage);
		return (NULL);
	}
	free(storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	char		*old_storage;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	while (!storage || !ft_strchr(storage, '\n'))
	{
		old_storage = storage;
		storage = read_and_update_storage(fd, storage);
		if (!storage)
			return (NULL);
		if (storage == old_storage && storage && !ft_strchr(storage, '\n'))
			break ;
	}
	if (!storage || !storage[0])
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	line = extract_line_from_storage(storage);
	storage = update_storage_after_extraction(storage);
	return (line);
}

// #include <string.h>

// int	main(void)
// {
// 	int fd = open("test_41.txt", O_RDONLY);
// 	char *line1 = get_next_line(fd);
// 	char *line2 = get_next_line(fd);
// 	printf("Line1: '%s' (len=%zu)\n", line1 ? line1 : "NULL",
// 		line1 ? strlen(line1) : 0);
// 	printf("Line2: '%s'\n", line2 ? line2 : "NULL");

// 	free(line1);
// 	free(line2);
// 	close(fd);
// }