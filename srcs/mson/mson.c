/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mson.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:52:30 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 18:21:11 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"
#include "get_next_line.h"

void	mson_parse_line(t_mson res, const char *line)
{
	if (*line == 'w' || *line == ' ')
		mson_map_add(res, line)
		
int		mson_parse_file(char *file)
{
	int		fd;
	char	*line;

	if ((fd = open(path, O_RDONLY) == -1))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '#')
			mson_parse_line(lvl, line);
		free(line);
	}
	free(line);
	return (1);
}
	
