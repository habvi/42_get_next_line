#include "get_next_line_bonus.h"

static bool	is_new_line(char *str)
{
	if (str == NULL)
		return (false);
	while (*str)
	{
		if (*str == LF)
			return (true);
		str++;
	}
	return (false);
}

static void	*ft_free(char *saved[], int fd, char *ps)
{
	if (saved[fd] != NULL)
	{
		free(saved[fd]);
		saved[fd] = NULL;
	}
	if (ps != NULL)
		free(ps);
	return (NULL);
}

static char	*read_buf(char *saved[], int fd, bool *finish_read)
{
	char	*buf;
	ssize_t	read_ret;

	buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	read_ret = read(fd, buf, BUFFER_SIZE);
	if (read_ret == READ_ERROR)
		return (ft_free(saved, fd, buf));
	buf[read_ret] = '\0';
	if (!read_ret)
		*finish_read = true;
	return (buf);
}

static char	*output(char *saved[], int fd)
{
	char	*ps;
	char	*left;
	char	*tail;

	ps = saved[fd];
	if (ps == NULL || *ps == '\0')
		return (ft_free(saved, fd, NULL));
	while (*ps && *ps != LF)
		ps++;
	left = ft_substr_for_gnl(saved[fd], 0, ps - saved[fd] + 1);
	if (left == NULL)
		return (ft_free(saved, fd, NULL));
	if (*left == '\0')
		return (ft_free(saved, fd, left));
	tail = ps;
	while (*tail)
		tail++;
	if (*ps == LF)
		ps++;
	saved[fd] = ft_memmove_for_gnl(saved[fd], ps, tail - ps + 1);
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*saved[MY_OPEN_MAX];
	bool		finish_read;
	char		*buf;
	char		*tmp;

	if (fd < 0 || fd >= MY_OPEN_MAX || \
		BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	finish_read = false;
	while (!finish_read)
	{
		if (is_new_line(saved[fd]))
			break ;
		buf = read_buf(saved, fd, &finish_read);
		if (buf == NULL)
			return (ft_free(saved, fd, NULL));
		tmp = ft_strjoin(saved[fd], buf);
		ft_free(saved, fd, buf);
		if (tmp == NULL)
			return (NULL);
		saved[fd] = tmp;
	}
	return (output(saved, fd));
}
