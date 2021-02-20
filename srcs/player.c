/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:45:42 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/20 11:34:36 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		player_is_near(t_obj *obj, t_player *plr)
{
	if (obj->x == plr->x && obj->y == plr->y)
		return (1);
	else
		return (0);
	/*
	if (obj->x == plr->x && (obj->y >= plr->y - 1 && obj->y <= plr->y + 1))
		return (1);
	if (obj->y == plr->y && (obj->x >= plr->x - 1 && obj->x <= plr->x + 1))
		return (1);
	return (0);
	*/
}

int		player_collision(char **map, t_obj *objs, t_player *plr, int y, int x)
{
	while (objs)
	{
		if (objs->ctl && objs->ctl->coll)
			if (objs->x == x && objs->y == y)
				if (objs->ctl->coll(objs, plr) == 0)
					return (0);
		objs = objs->next;
	}
	if (map[y][x] != '.')
		return (0);
	return (1);
}

int		player_move(t_level *lvl, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_w &&
			player_collision(lvl->map, lvl->objs, lvl->plr, lvl->plr->y-1, lvl->plr->x))
		lvl->plr->y -= 1;
	else if (event.key.keysym.sym == SDLK_s &&
			player_collision(lvl->map, lvl->objs, lvl->plr, lvl->plr->y+1, lvl->plr->x))
		lvl->plr->y += 1;
	else if (event.key.keysym.sym == SDLK_a &&
			player_collision(lvl->map, lvl->objs, lvl->plr, lvl->plr->y, lvl->plr->x-1))
		lvl->plr->x -= 1;
	else if (event.key.keysym.sym == SDLK_d &&
			player_collision(lvl->map, lvl->objs, lvl->plr, lvl->plr->y, lvl->plr->x+1))
		lvl->plr->x += 1;
	else if (event.key.keysym.sym == SDLK_SPACE)
		egg_drop(lvl->plr);
	else if (event.key.keysym.sym == SDLK_r)
		egg_hatch(lvl->plr);
	else if (event.key.keysym.sym == SDLK_e)
		object_act(lvl->objs, lvl->plr);
	else if (event.key.keysym.sym == SDLK_q)
		return (-1);
	else if (event.key.keysym.sym == SDLK_z)
		return (0);
	return (1);
}
