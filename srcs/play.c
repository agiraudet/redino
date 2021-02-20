/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:40:27 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/20 05:24:04 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		play_lvl_exist(const char *file)
{
	struct stat	buffer;
	int			exist;

	exist = stat(file, &buffer);
	if (exist == 0)
		return (1);
	else
		return (0);
}

void	play_loop_update(t_scene *sc, t_level *lvl, int old_x, int old_y)
{
	object_update(lvl->objs);
	scene_blit_sprite(sc, scene_get_sprite_nb(lvl->map[old_y][old_x]), old_x, old_y);
	scene_blit_sprite(sc, scene_get_sprite_nb(lvl->map[lvl->plr->y][lvl->plr->x]), lvl->plr->x, lvl->plr->y);
	render_objs(sc, lvl->objs, lvl->map);
	render_egg(sc, lvl->plr);
	render_player(sc, lvl->plr);
	SDL_UpdateWindowSurface(sc->win);
}

int		play_level(t_scene *sc, t_level *lvl)
{
	SDL_Event	event;
	int			stat;
	int			old_x;
	int			old_y;

	scene_fill_bg(sc, 0x0);
	object_update(lvl->objs);
	render_level(sc, lvl);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return (0);
			else if (event.type == SDL_KEYDOWN)
			{
				old_x = lvl->plr->x;
				old_y = lvl->plr->y;
				stat = player_move(lvl, event);
				play_loop_update(sc, lvl, old_x, old_y);
				if (lvl->plr->win)
					return (1);
				if (stat != 1)
					return (stat);
			}
		}
	}
	return (0);
}

int		play_all_level(t_scene *sc, const char *lvl_path)
{
	char		*lvl_list[] =
	{"lvl_00", "lvl_01", "lvl_02", "lvl_03", "lvl_04",
	"lvl_05", "lvl_06", "lvl_07", "lvl_08", 0};

	char		*lvl_name;
	t_level		*lvl;
	int			stat;
	int			i;

	i = 0;
	lvl = 0;
	while (lvl_list[i])
	{
		lvl_name = ft_strjoin(lvl_path, lvl_list[i]);
		if (!play_lvl_exist(lvl_name))
		{
			i++;
			free(lvl_name);
			continue ;
		}
		lvl = level_load(lvl_name);
		if (!lvl)
			return (0);
		scene_set_offset(sc, lvl->map);
		stat = play_level(sc, lvl);
		level_destroy(lvl);
		free(lvl_name);
		if (stat == 1)
			i++;
		else if (stat == -1)
			return (0);
	}
	return (1);
}
