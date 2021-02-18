/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 21:52:09 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 21:59:40 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

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
