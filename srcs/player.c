/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:45:42 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/23 16:29:08 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		player_behind_obj(t_player *plr, t_obj *obj)
{
	if (strcmp(obj->type, "check") == 0)
		return (0);
	if (strcmp(obj->type, "spike") == 0 && obj->status == DEACT)
		return (0);
	if( plr->y <= (double)obj->y && plr->y > (double)obj->y - 0.7)
		return (1);
	return (0);
}

int		player_is_near(double plr_x, double plr_y, int x, int y)
{
	double	dist;

	dist = sqrt(pow((double)x - plr_x, 2) + pow((double)y - plr_y, 2));
	if (dist <= HITBOX)
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

int		player_move(t_level *lvl, t_timer *time)
{
	if (lvl->inp->up && player_collision(lvl, lvl->plr->y-PLAYER_SPEED, lvl->plr->x))
		lvl->plr->y -= PLAYER_SPEED;
	if (lvl->inp->down && player_collision(lvl, lvl->plr->y+PLAYER_SPEED, lvl->plr->x))
		lvl->plr->y += PLAYER_SPEED;
	if (lvl->inp->left && player_collision(lvl, lvl->plr->y, lvl->plr->x-PLAYER_SPEED))
		lvl->plr->x -= PLAYER_SPEED;
	if (lvl->inp->right && player_collision(lvl, lvl->plr->y, lvl->plr->x+PLAYER_SPEED))
		lvl->plr->x += PLAYER_SPEED;
	if (lvl->inp->egg)
		if (timer_check_cd(time, ACT_EGG, CD_EGG))
		{
			egg_drop(lvl);
			timer_reset_cd(time, ACT_EGG);
		}
	if (lvl->inp->hatch)
		if (timer_check_cd(time, ACT_HATCH, CD_HATCH))
		{
			egg_hatch(lvl->plr);
			timer_reset_cd(time, ACT_HATCH);
		}
	if (lvl->inp->act)
		if (timer_check_cd(time, ACT_ACT, CD_ACT))
		{
			object_act(lvl->objs, lvl->plr);
			timer_reset_cd(time, ACT_ACT);
		}
	if (lvl->inp->quit)
		return (-1);
	if (lvl->inp->reset)
		return (0);
	return (1);
}
