/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzolarue <enzolarue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:46:21 by enzolarue         #+#    #+#             */
/*   Updated: 2025/12/03 15:08:24 by enzolarue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*read_and_update_storage(int fd, char *storage)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	num_read;
	int		i;
	char	*temp_storage;
	char	*cut_buff;

	num_read = read(fd, buf, BUFFER_SIZE);
	if (num_read <= 0)
		return (storage);
	buf[num_read] = '\0';
	i = -1;
	while (++i < num_read)
	{
		if (buf[i] == '\n')
		{
			cut_buff = ft_substr(buf, 0, i + 1);
			temp_storage = ft_strjoin(storage, cut_buff);
			free(storage);
			free(cut_buff);
			return (temp_storage);
		}
	}
	temp_storage = ft_strjoin(storage, buf);
	free(storage);
	return (temp_storage);
}

char	*extract_line_from_storage(char *storage)
{
	char	*after_line;
	size_t			len;

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

	after_line = ft_strchr(storage, '\n');
	if (!after_line)
	{
		free(storage);
		return (NULL);
	}
	if (!after_line[1])
	{
		free(storage);
		return (NULL);
	}
	new_storage = ft_strdup(after_line + 1);
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
		if (storage == old_storage && (!storage || !ft_strchr(storage, '\n')))
			break ;
	}
	if (!storage || !*storage)
		return (NULL);
	line = extract_line_from_storage(storage);
	storage = update_storage_after_extraction(storage);
	return (line);
}

// int	main(void)
// {
// 	int fd;

// 	fd = open("text.txt", O_RDONLY);
// 	if (fd != -1)
// 		get_next_line(fd);
// 	else
// 	{
// 		printf("ERROR opening file");
// 		return (-1);
// 	}
// 	return (0);
// }
