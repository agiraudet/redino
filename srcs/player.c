/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:45:42 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/22 00:20:03 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		player_is_near(double plr_x, double plr_y, int x, int y)
{
	if ((double)x >= plr_x - HITBOX && (double)x <= plr_x + HITBOX)
		if ((double)y >= plr_y - HITBOX && (double)y <= plr_y + HITBOX)
			return (1);
	return (0);
}

int		player_collision(t_level *lvl, double y, double x)
{
	t_obj	*objs;
	char	tile_r;
	char	tile_l;

	objs = lvl->objs;
	while (objs)
	{
		if (objs->ctl && objs->ctl->coll)
			if (player_is_near(x, y, objs->x, objs->y))
				if (objs->ctl->coll(objs, lvl->plr) == 0)
					return (0);
		objs = objs->next;
	}
	tile_r = lvl->map[(int)ceil(y)][(int)ceil(x)];
	tile_l = lvl->map[(int)ceil(y)][(int)floor(x)];
	if (tile_r != '.' || tile_l != '.')
		return (0);
	return (1);
}

int		player_move(t_level *lvl, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_w &&
			player_collision(lvl, lvl->plr->y-PLAYER_SPEED, lvl->plr->x))
		lvl->plr->y -= PLAYER_SPEED;
	else if (event.key.keysym.sym == SDLK_s &&
			player_collision(lvl, lvl->plr->y+PLAYER_SPEED, lvl->plr->x))
		lvl->plr->y += PLAYER_SPEED;
	else if (event.key.keysym.sym == SDLK_a &&
			player_collision(lvl, lvl->plr->y, lvl->plr->x-PLAYER_SPEED))
		lvl->plr->x -= PLAYER_SPEED;
	else if (event.key.keysym.sym == SDLK_d &&
			player_collision(lvl, lvl->plr->y, lvl->plr->x+PLAYER_SPEED))
		lvl->plr->x += PLAYER_SPEED;
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
