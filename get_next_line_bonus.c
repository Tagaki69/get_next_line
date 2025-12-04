/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elarue <elarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:46:21 by enzolarue         #+#    #+#             */
/*   Updated: 2025/12/04 12:00:21 by elarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[1024];
	char		*line;
	char		*old_stash;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	while (!stash[fd] || !ft_strchr(stash[fd], '\n'))
	{
		old_stash = stash[fd];
		stash[fd] = read_and_update_stash(fd, stash[fd]);
		if (!stash[fd])
			return (NULL);
		if (stash[fd] == old_stash && stash[fd] && !ft_strchr(stash[fd], '\n'))
			break ;
	}
	if (!stash[fd] || !stash[fd][0])
	{
		stash[fd] = NULL;
		return (free(stash[fd]), NULL);
	}
	line = extract_line_from_stash(stash[fd]);
	if (!line)
		return (ft_free(line, &stash[fd]));
	stash[fd] = update_stash_after_extraction(stash[fd]);
	return (line);
}

// #include <stdio.h>

// void	print_line(int fd, char *filename, int *active_fds)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	if (line)
// 	{
// 		printf("[%s] : |%s|", filename, line);
// 		if (ft_strchr(line, '\n') == NULL)
// 			printf(" (EOF sans \\n)");
// 		printf("\n");
// 		free(line);
// 	}
// 	else
// 	{
// 		if (*active_fds > 0)
// 			printf("[%s] : --- FIN DU FICHIER ---\n", filename);
// 		(*active_fds)--;
// 	}
// }

// int	main(void)
// {
// 	int fd1, fd2, fd3;
// 	int files_open;

// 	fd1 = open("file1", O_RDONLY);
// 	fd2 = open("file2", O_RDONLY);
// 	fd3 = open("file3", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
// 	{
// 		printf("Erreur : Creez file1, file2 et file3\n");
// 		return (1);
// 	}
// 	printf("---- DEBUT DU TEST BONUS (BUFFER_SIZE = %d) ----\n", BUFFER_SIZE);
// 	files_open = 3;
// 	while (files_open > 0)
// 	{
// 		files_open = 3;
// 		print_line(fd1, "file1", &files_open);
// 		print_line(fd2, "file2", &files_open);
// 		print_line(fd3, "file3", &files_open);
// 		printf("--------------------------------\n");
// 		if (files_open == 0)
// 			break ;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	printf("---- TEST TERMINE ----\n");
// 	return (0);
// }