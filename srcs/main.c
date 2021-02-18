/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:21:04 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 17:39:47 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		win()
{
	endwin();
	exit(0);
}

int		main(void)
{
	t_level		*lvl;

	init_ncurse();
	if (!(lvl = level_load()))
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
