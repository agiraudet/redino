/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:23:56 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/24 23:52:10 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		getnl(const char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		slen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*ret;
	int		i;

	ret = (char*)malloc(sizeof(char) * (slen(str) + 1));
	if (!ret)
		return (0);
	i = 0;
	while (*str)
		ret[i++] = *str++;
	ret[i] = '\0';
	return (ret);
}

int		clean_join(char **cont, char *buf)
{
	char	*new_cont;
	int		i;

	new_cont = (char*)malloc(sizeof(char) * (slen(*cont) + slen(buf) + 1));
	if (!new_cont)
	{
		if (*cont)
			free(*cont);
		return (0);
	}
	i = 0;
	while (*cont && (*cont)[i])
	{
		new_cont[i] = (*cont)[i];
		i++;
	}
	while (*buf)
		new_cont[i++] = *buf++;
	new_cont[i] = '\0';
	if (*cont)
		free(*cont);
	*cont = new_cont;
	return (1);
}

int		get_first_line(char **line, char **cont)
{
	int		i;
	int		end;
	char	*new_cont;

	if (!(*line = (char*)malloc(sizeof(char) * (slen(*cont) + 2))))
	{
		free(*cont);
		return (-1);
	}
	i = 0;
	while ((*cont)[i] && (*cont)[i] != '\n')
	{
		(*line)[i] = (*cont)[i];
		i++;
	}
	(*line)[i] = '\0';
	end = (*cont)[i] == '\n' ? 1 : 0;
	if ((*cont)[i] == '\n')
		i++;
	if (!(new_cont = ft_strdup(*cont + i)))
		end = -1;
	if (*cont)
		free(*cont);
	*cont = end > -1 ? new_cont : 0;
	return (end);
}
