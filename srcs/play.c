/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:40:27 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 18:40:28 by agiraude         ###   ########.fr       */
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

int		play_level(t_level *lvl)
{
	int		stat;

	while (1)
	{
		object_update(lvl->objs);
		render_level(lvl);
		stat = player_move(lvl->map, lvl->objs, lvl->plr);
		if (lvl->plr->win)
			return (1);
		if (stat != 1)
			return (stat);
	}
}

int		play_all_lvl(const char *lvl_path)
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
		stat = play_level(lvl);
		render_clean_screen();
		level_destroy(lvl);
		free(lvl_name);
		if (stat == 1)
			i++;
		else if (stat == -1)
			return (0);
	}
	return (1);
}

int		play_solo_lvl(char *lvl_path)
{
	t_level	*lvl;
	int		stat;

	stat = 0;
	if (play_lvl_exist(lvl_path))
	{
		while (stat == 0)
		{
			lvl = level_load(lvl_path);
			if (!lvl)
				return (0);
			stat = play_level(lvl);
			render_clean_screen();
			level_destroy(lvl);
			if (stat == 1)
				return (1);
		}
	}
	return (0);
}