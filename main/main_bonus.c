#include "../get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line1;
	char	*line2;
	char	*line3;

	fd1 = open("test/test1.txt", O_RDONLY);
	fd2 = open("test/test2.txt", O_RDONLY);
	fd3 = open("test/test3.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		perror("open");
		return (1);
	}
	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);
		if (!line1 && !line2 && !line3)
			break ;
		if (line1)
		{
			printf("FD1: %s", line1);
			free(line1);
		}
		if (line2)
		{
			printf("FD2: %s", line2);
			free(line2);
		}
		if (line3)
		{
			printf("FD3: %s", line3);
			free(line3);
		}
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
