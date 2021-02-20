/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:21:04 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/20 03:39:08 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		main(int argc, char **argv)
{
	t_scene		*sc;
	t_level		*lvl;

	if (!(sc = scene_create("redino", 640, 480)))
		return (1);
	if (!(scene_load_atlas(sc, "assets/atlas.bmp")))
	{
		scene_destroy(sc);
		return (1);
	}
	lvl = level_load("levels/lvl_01");
	scene_set_offset(sc, lvl->map);
	play_all_level_sdl(sc, "levels/");
	level_destroy(lvl);
	scene_destroy(sc);
	return (0);
}
