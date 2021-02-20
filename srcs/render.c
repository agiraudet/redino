/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:03:17 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/20 18:31:52 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void	render_map(t_scene *sc, char **map)
{
	int		y;
	int		x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			scene_blit_sprite(sc, scene_get_sprite_nb(map[y][x]), x, y, -1);
			x++;
		}
		y++;
	}
}

void	render_objs(t_scene *sc, t_obj *objs, char **map)
{
	while (objs)
	{
		scene_blit_sprite(sc, scene_get_sprite_nb(map[objs->y][objs->x]), objs->x, objs->y, -1);
		scene_blit_sprite(sc, objs->sprite[objs->frame], objs->x, objs->y, objs->color);
		objs = objs->next;
	}
}

void	render_egg(t_scene *sc, t_player *plr)
{
	int		i;

	i = plr->egc - 1;
	while (i >= 0)
	{
		scene_blit_sprite(sc, plr->sprite_egg[plr->egg[i].frame],
				plr->egg[i].x, plr->egg[i].y, plr->color);
		i--;
	}
}

void	render_player(t_scene *sc, t_player *plr)
{
	scene_blit_sprite(sc, plr->sprite[plr->frame], plr->x, plr->y, plr->color);
}

void	render_level(t_scene *sc ,t_level *lvl)
{
	render_map(sc, lvl->map);
	render_objs(sc, lvl->objs, lvl->map);
	render_egg(sc, lvl->plr);
	render_player(sc, lvl->plr);
	scene_update(sc);
}
