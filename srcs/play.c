/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:40:27 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/23 16:22:22 by agiraude         ###   ########.fr       */
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

int		play_level(t_scene *sc, t_level *lvl)
{
	SDL_Event	event;
	int			stat;

	timer_update(&sc->time);
	timer_init_cd(&sc->time);
	render_level(sc, lvl);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return (0);
			else if (event.type == SDL_KEYDOWN)
				input(lvl->inp, event.key.keysym.sym, KEY_DOWN);
			else if (event.type == SDL_KEYUP)
				input(lvl->inp, event.key.keysym.sym, KEY_UP);
		}
		stat = player_move(lvl, &sc->time);
		object_update(lvl->objs);
		timer_update(&sc->time);
		render_level(sc, lvl);
		if (lvl->plr->win)
			return (1);
		if (stat != 1)
			return (stat);
	}
	return (0);
}

int		play_one_level(t_scene *sc, char *lvl_path)
{
	t_level	*lvl;
	int		stat;

	if (!play_lvl_exist(lvl_path))
		return (0);
	stat = 0;
	while (stat >= 0)
	{
		lvl = level_load(lvl_path);
		level_init(sc, lvl);
		stat = play_level(sc, lvl);
		level_destroy(lvl);
		if (lvl->plr->win)
			return (1);
	}
	return (0);
}

int		play_all_level(t_scene *sc, const char *lvl_path)
{
	char		*lvl_list[] =
	{"lvl_00", "lvl_01", "lvl_02", "lvl_03", "lvl_04",
	"lvl_05", "lvl_06", "lvl_07", "lvl_08", "lvl_09", 0};

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
		level_init(sc, lvl);
		if (!lvl)
			return (0);
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
