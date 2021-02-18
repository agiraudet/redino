/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:20:41 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/25 01:34:18 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_error(int fd, char **line, char **buffer)
{
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (0);
	if (!(*buffer = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (0);
	return (1);
}

int		end_of_file(int rd, int keepgoing, char **content)
{
	if (!rd && !keepgoing)
	{
		if (*content)
		{
			free(*content);
			*content = 0;
		}
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*content = 0;
	char		*buffer;
	int			rd;
	int			keepgoing;

	rd = 1;
	if (!check_error(fd, line, &buffer))
		return (-1);
	while (getnl(content) == -1 && (rd = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rd] = '\0';
		rd = clean_join(&content, buffer) ? 1 : -1;
	}
	free(buffer);
	if (rd == -1)
		return (-1);
	if (!content)
	{
		keepgoing = 0;
		*line = ft_strdup("");
	}
	else if ((keepgoing = get_first_line(line, &content)) == -1)
		return (-1);
	return (end_of_file(rd, keepgoing, &content));
}
