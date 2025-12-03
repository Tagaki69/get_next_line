/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzolarue <enzolarue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:46:21 by enzolarue         #+#    #+#             */
/*   Updated: 2025/12/02 17:11:23 by enzolarue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*read_and_update_storage(int fd, char *storage)
{
	char 	buf[BUFFER_SIZE + 1];
	ssize_t	num_read;
	int	i;
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
			temp_storage = ft_strjoin (storage, cut_buff);
			free (storage);
			free (cut_buff);
			return (temp_storage);
		}
	}
	temp_storage = ft_strjoin(storage, buf);
	free(storage);
	return (temp_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char			*line;
	

	if (BUFFER_SIZE <= 0 || fd < 0)
	return (NULL);
	storage = read_and_update_storage(fd, storage);
	if (!storage)
		return (NULL);
	
}


int	main(void)
{
	int fd;

	fd = open("text.txt", O_RDONLY);
	if (fd != -1)
		get_next_line(fd);
	else
	{
		printf("ERROR opening file");
		return (-1);
	}
}