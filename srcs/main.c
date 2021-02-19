/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:21:04 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 01:29:17 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		win()
{
	endwin();
	exit(0);
}

int		main(int argc, char **argv)
{
	t_level		*lvl;
	char		*lvl_file;

	if (argc < 2)
		lvl_file = strdup("levels/lvl_test");
	else
		lvl_file = argv[1];
	init_ncurse();
	if (!(lvl = level_load(lvl_file)))
	{
		endwin();
		return (0);
	}
	while (1)
	{
		object_update(lvl->objs);
		render_level(lvl);
		if (!player_move(lvl->map, lvl->objs, lvl->plr))
			break;
	}
//	level_destroy(lvl);
	endwin();
	return (0);
}
