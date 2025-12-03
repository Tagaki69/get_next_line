#ifndef get_next_line
# define BUFFER_SIZE 1024

# include <unistd.h>
# include <fcntl.h>

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif