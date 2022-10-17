#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
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
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len_s;
	char	*dst;

	len_s = ft_strlen(s);
	dst = (char *)malloc(sizeof(char) * (len_s + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s, len_s + 1);
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	total;
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	total = len_s1 + len_s2;
	res = (char *)malloc(sizeof(char) * (total + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, len_s1 + 1);
	ft_strlcpy(res + len_s1, s2, len_s2 + 1);
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	tail;
	size_t	len_substr;
	char	*res;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s <= start || len == 0)
		len_substr = 0;
	else
	{
		if (len_s <= start + len)
			tail = len_s;
		else
			tail = start + len;
		len_substr = tail - start;
	}
	res = (char *)malloc(sizeof(char) * (len_substr + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s + start, len_substr + 1);
	return (res);
}
