#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

static void	ft_strlcpy_for_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_substr_for_gnl(s2, 0, ft_strlen(s2)));
	if (s2 == NULL)
		return (ft_substr_for_gnl(s1, 0, ft_strlen(s1)));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy_for_gnl(res, s1, len_s1 + 1);
	ft_strlcpy_for_gnl(res + len_s1, s2, len_s2 + 1);
	return (res);
}

char	*ft_substr_for_gnl(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (s == NULL)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy_for_gnl(res, s + start, len + 1);
	return (res);
}

void	*ft_memmove_for_gnl(void *dst, const void *src, size_t len)
{
	unsigned char		*pd;
	const unsigned char	*ps = (const unsigned char *)src;
	size_t				i;

	if (dst == src)
		return (dst);
	pd = (unsigned char *)dst;
	i = 0;
	while (i < len)
	{
		if (dst < src)
			pd[i] = ps[i];
		else
			pd[len - i - 1] = ps[len - i - 1];
		i++;
	}
	return (dst);
}
