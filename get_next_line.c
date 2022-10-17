#include "get_next_line.h"

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

static void	*ft_free(char **saved, char *ps, bool free_ps)
{
	if (*saved != NULL)
	{
		free(*saved);
		*saved = NULL;
	}
	if (free_ps)
		free(ps);
	return (NULL);
}

static char	*read_mode(char **saved, int fd, bool *fin_read)
{
	char	*buf;
	int		read_size;

	buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size == READ_ERROR)
		return (ft_free(saved, buf, true));
	buf[read_size] = '\0';
	if (read_size < BUFFER_SIZE)
		*fin_read = true;
	return (buf);
}

static char	*output(char **saved)
{
	char	*ps;
	char	*left;
	char	*right;
	char	*tail;

	ps = *saved;
	if (!ps || *ps == '\0')
		return (ft_free(saved, NULL, false));
	while (*ps && *ps != LF)
		ps++;
	left = ft_substr(*saved, 0, ps - *saved + 1);
	if (left == NULL)
		return (ft_free(saved, NULL, false));
	if (*left == '\0')
		return (ft_free(saved, left, true));
	tail = ps;
	while (*tail)
		tail++;
	right = ft_substr(ps + 1, 0, tail - ps);
	if (right == NULL)
		return (ft_free(saved, left, true));
	free(*saved);
	*saved = right;
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	bool		fin_read;
	char		*buf;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (saved == NULL)
	{
		saved = (char *)malloc(sizeof(char) * 1);
		*saved = '\0';
	}
	fin_read = false;
	while (!fin_read)
	{
		if (is_new_line(saved))
			break ;
		buf = read_mode(&saved, fd, &fin_read);
		if (buf == NULL)
			return (ft_free(&saved, buf, false));
		tmp = ft_strjoin(saved, buf);
		ft_free(&saved, buf, true);
		saved = tmp;
	}
	return (output(&saved));
}
