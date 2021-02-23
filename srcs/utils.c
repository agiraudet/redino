/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 21:52:09 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/23 14:48:13 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

static size_t	uint32_t_len(uint32_t nb)
{
	size_t	len;

	len = 1;
	while (nb > 9)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char		*ft_u32toa(uint32_t n)
{
	char	*str;
	size_t	i;

	i = uint32_t_len(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i--] = 0;
	while (i >= 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		if (i == 0)
			break;
		i--;
	}
	return (str);
}

void		hex_to_sdl_color(int hex, SDL_Color *color)
{
	color->r = (hex >> 16) & 0xFF;
	color->g = (hex >> 8) & 0xFF;
	color->b = hex & 0xFF;
}

void		hex_to_rgb(int hex, int *r, int *g, int *b)
{
	*r = (hex >> 16) & 0xFF;
	*g = (hex >> 8) & 0xFF;
	*b = hex & 0xFF;
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	if (!s)
		return (0);
	if (start >= strlen(s))
		return (strdup(""));
	ret = (char*)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	i = 0;
	while (len-- && s[start])
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}

static int	ft_getindex(const char *s, char c)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	count_str(const char *str, const char *sep)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] && ft_getindex(sep, str[i]) != -1)
		i++;
	while (str[i])
	{
		count++;
		while (str[i] && ft_getindex(sep, str[i]) == -1)
			i++;
		while (str[i] && ft_getindex(sep, str[i]) != -1)
			i++;
	}
	return (count);
}

static char	**destroy_ret(char **ret, int i)
{
	i--;
	while (i >= 0)
		free(ret[i--]);
	free(ret);
	return (0);
}

char		**ft_nsplit(const char *str, const char *sep)
{
	char	**ret;
	int		len;
	int		i;

	if (!str)
		return (0);
	if (!(ret = malloc(sizeof(char*) * (count_str(str, sep) + 1))))
		return (0);
	i = 0;
	while (*str)
	{
		while (*str && ft_getindex(sep, *str) != -1)
			str++;
		if (*str && ft_getindex(sep, *str) == -1)
		{
			len = 0;
			while (str[len] && ft_getindex(sep, str[len]) == -1)
				len++;
			if (!(ret[i++] = ft_substr(str, 0, len)))
				return (destroy_ret(ret, i));
			str += len;
		}
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	ret = (char*)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!ret)
		return (0);
	i = 0;
	while (*s1)
		ret[i++] = *s1++;
	while (*s2)
		ret[i++] = *s2++;
	ret[i] = '\0';
	return (ret);
}
