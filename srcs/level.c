/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:07:37 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/21 18:44:48 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void	level_plr_destroy(t_player *plr)
{
	free(plr->egg);
	free(plr->sprite);
	free(plr);
}

void		level_obj_destroy(t_obj *obj_lst)
{
	t_obj	*tmp;

	while (obj_lst)
	{
		tmp = obj_lst->next;
		object_destroy(obj_lst);
		obj_lst = tmp;
	}
}

void	level_map_destroy(char **map)
{
	int		i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void		level_set_map_size(t_level *lvl)
{
	int		x;
	int		max_x;
	int		y;

	y = 0;
	max_x = 0;
	while (lvl->map[y])
	{
		x = 0;
		while (lvl->map[y][x])
			x++;
		if (max_x < x)
			max_x = x;
		y++;
	}
	lvl->map_size_x = max_x;
	lvl->map_size_y = y;
}

t_level		*level_load(char *lvl_file)
{
	t_level *lvl;

	if (!(lvl = loader_parse_file(lvl_file)))
		return (0);
	level_set_map_size(lvl);
	return (lvl);
}

void		level_destroy(t_level *lvl)
{
		level_obj_destroy(lvl->objs);
		level_map_destroy(lvl->map);
		level_plr_destroy(lvl->plr);
		if (lvl->hint)
			free(lvl->hint);
		if (lvl->name)
			free(lvl->name);
		free(lvl);
}
