/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:07:37 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 18:44:55 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

t_player *level_plr_init()
{
	t_player	*plr;

	plr = malloc(sizeof(t_player));
	plr->x = 5;
	plr->y = 5;
	plr->chr = "P";
	plr->color = 0;
	return (plr);
}

void	level_plr_destroy(t_player *plr)
{
	free(plr);
}

t_obj	*level_obj_init2()
{
	t_obj	*obj_lst;
	t_obj	*obj_tmp;
	t_ctl	*ctl_tmp;

	obj_lst = 0;

	ctl_tmp = ctl_create(0, &obj_portal_coll, 0, 0, 0);
	obj_tmp = object_create("O", PORTAL, 3, 3, BLUE, ACT, ctl_tmp);
	object_add(&obj_lst, obj_tmp);

	ctl_tmp = ctl_create(&obj_lever_act, 0, 0, &obj_lever_update, 1);
	obj_tmp = object_create("/", LEVER, 20, 4, GREEN, DEACT, ctl_tmp);
	object_add(&obj_lst, obj_tmp);

	ctl_tmp = ctl_create(0, &obj_door_coll, &logic_and, &obj_door_update, 1);
	obj_tmp = object_create("-", DOOR, 29, 4, NONE, DEACT, ctl_tmp);
	object_add(&obj_lst, obj_tmp);

	return (obj_lst);
}


t_obj		**level_obj_init()
{
	t_obj	**objs;
	t_ctl		*ctl;
	int			nb_obj = 9;
	int			i;

	objs = malloc(sizeof(t_obj*) * (nb_obj + 1));
	i = 0;
	ctl = ctl_create(0, &obj_portal_coll, 0, 0, 0);
	objs[i++] = object_create("O", PORTAL, 3, 3, BLUE, ACT, ctl);
	objs[i++] = object_create("O", PORTAL, 8, 8, RED, ACT, ctl);
	objs[i++] = object_create("O", PORTAL, 8, 4, GREEN, ACT, ctl);
	objs[i++] = object_create("O", PORTAL, 5, 2, WHITE, ACT, ctl);
	ctl = ctl_create(0, &obj_spike_coll, 0, 0, 0);
	objs[i++] = object_create(".", SPIKE, 26, 7, RED, ACT, ctl);
	objs[i++] = object_create(".", SPIKE, 27, 7, RED, ACT, ctl);
	objs[i++] = object_create(".", SPIKE, 28, 7, RED, ACT, ctl);
	ctl = ctl_create(&obj_lever_act, 0, 0, &obj_lever_update, 1);
	objs[i++] = object_create("/", LEVER, 20, 4, GREEN, DEACT, ctl);
	ctl = ctl_create(0, &obj_door_coll, &logic_and, &obj_door_update, 1);
	objs[i++] = object_create("-", DOOR, 29, 4, NONE, DEACT, ctl);
	objs[i] = 0;
	ctl_build_all(objs);
	return (objs);
}

void		level_obj_destroy2(t_obj *obj_lst)
{
	t_obj	*tmp;

	while (obj_lst)
	{
		tmp = obj_lst->next;
		object_destroy(obj_lst);
		obj_lst = tmp;
	}
}

void		level_obj_destroy(t_obj **objs)
{
	int		i;

	i = 0;
	while (objs[i])
		object_destroy(objs[i++]);
	free(objs);
}


char		**level_map_init(int size_x, int size_y)
{
	char	**map;
	int		i;
	int		ii;

	map = malloc(sizeof(char*) * (size_y + 1));
	i = 0;
	while (i < size_y)
	{
		map[i] = malloc(sizeof(char) * (size_x + 1));
		ii = 0;
		while (ii < size_x)
		{
			if (i == 0 || i == size_y - 1 || ii == 0 || ii == size_x -1)
				map[i][ii++] = 'w';
			else
				map[i][ii++] = '.';
		}
		map[i++][ii] = 0;
	}
	map[i] = 0;
	return (map);
}

void	level_map_destroy(char **map)
{
	int		i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

t_level		*level_load()
{
	t_level *lvl;

	if (!(lvl = malloc(sizeof(t_level))))
		return (0);
	if (!(lvl->objs = level_obj_init()))
	{
		free(lvl);
		return (0);
	}
	if (!(lvl->map = level_map_init(30, 10)))
	{
		level_obj_destroy(lvl->objs);
		free(lvl);
		return (0);
	}
	if (!(lvl->plr = level_plr_init()))
	{
		level_obj_destroy(lvl->objs);
		level_map_destroy(lvl->map);
		free(lvl);
		return (0);
	}
	return (lvl);
}

void		level_destroy(t_level *lvl)
{
		level_obj_destroy(lvl->objs);
		level_map_destroy(lvl->map);
		level_plr_destroy(lvl->plr);
		free(lvl);
}
