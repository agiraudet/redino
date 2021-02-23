/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 00:52:14 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/23 16:00:17 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		egg_check_if_obj_up(t_obj *objs, t_obj *self)
{
	while (objs)
	{
		if (objs != self && objs->x == self->x && objs->y == self->y + 1)
			return (1);
		objs = objs->next;
	}
	return (0);
}

int		egg_check_pos(t_level *lvl)
{
	t_obj	*objs;
	int		i;

	i = lvl->plr->egc - 1;
	while (i >= 0)
	{
		if (lvl->plr->egg[i].x == lvl->plr->x && lvl->plr->egg[i].y == lvl->plr->y)
			return (0);
		i--;
	}
	objs = lvl->objs;
	while (objs)
	{
		if (player_is_near(lvl->plr->x, lvl->plr->y, objs->x, objs->y))
			if (strstr("check spike", objs->type) != 0)
				return (0);
		objs = objs->next;
	}
	return (1);
}

int		egg_drop(t_level *lvl)
{
	if (lvl->plr->egc < lvl->plr->max_egg && egg_check_pos(lvl))
	{
		lvl->plr->egg[lvl->plr->egc].x = lvl->plr->x;
		lvl->plr->egg[lvl->plr->egc].y = lvl->plr->y;
		lvl->plr->egg[lvl->plr->egc].frame = 0;
		lvl->plr->egc++;
		return (1);
	}
	return (0);
}

void	egg_hatch(t_player *plr)
{
	if (plr->egc > 0)
	{
		plr->x = plr->egg[plr->egc - 1].x;
		plr->y = plr->egg[plr->egc - 1].y;
		plr->egc--;
	}
}
