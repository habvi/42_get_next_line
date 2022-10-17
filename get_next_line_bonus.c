#include "get_next_line_bonus.h"

static bool	is_new_line(char *str)
{
	size_t	i;

	if (str == NULL)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == LF)
			return (true);
		i++;
	}
	return (false);
}

static void	*ft_free(char *saved[], int fd, char *ps, bool free_ps)
{
	if (saved[fd] != NULL)
	{
		free(saved[fd]);
		saved[fd] = NULL;
	}
	if (free_ps)
		free(ps);
	return (NULL);
}

static char	*read_mode(char *saved[], int fd, bool *fin_read)
{
	char	*buf;
	int		read_size;

	buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size == READ_ERROR)
		return (ft_free(saved, fd, buf, true));
	buf[read_size] = '\0';
	if (read_size < BUFFER_SIZE)
		*fin_read = true;
	return (buf);
}

static char	*output(char *saved[], int fd)
{
	char	*ps;
	char	*left;
	char	*right;
	char	*tail;

	ps = saved[fd];
	if (!ps || *ps == '\0')
		return (ft_free(saved, fd, NULL, false));
	while (*ps && *ps != LF)
		ps++;
	left = ft_substr(saved[fd], 0, ps - saved[fd] + 1);
	if (left == NULL)
		return (ft_free(saved, fd, NULL, false));
	if (*left == '\0')
		return (ft_free(saved, fd, left, true));
	tail = ps;
	while (*tail)
		tail++;
	right = ft_substr(ps + 1, 0, tail - ps);
	if (right == NULL)
		return (ft_free(saved, fd, left, true));
	free(saved[fd]);
	saved[fd] = right;
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*saved[1025];
	bool		fin_read;
	char		*buf;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (saved[fd] == NULL)
	{
		saved[fd] = (char *)malloc(sizeof(char) * 1);
		*saved[fd] = '\0';
	}
	fin_read = false;
	while (!fin_read)
	{
		if (is_new_line(saved[fd]))
			break ;
		buf = read_mode(saved, fd, &fin_read);
		if (buf == NULL)
			return (ft_free(saved, fd, buf, false));
		tmp = ft_strjoin(saved[fd], buf);
		ft_free(saved, fd, buf, true);
		saved[fd] = tmp;
	}
	return (output(saved, fd));
}
