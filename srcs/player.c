/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:45:42 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 17:33:23 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		player_collision(char **map, t_obj **objs, t_player *plr, int y, int x)
{
	int		i;

	i = 0;
	while (objs[i])
	{
		if (objs[i]->ctl && objs[i]->ctl->coll)
			if (objs[i]->x == x && objs[i]->y == y)
				if (objs[i]->ctl->coll(objs[i], plr) == 0)
					return (0);
		i++;
	}
	if (map[y][x] != '.')
		return (0);
	return (1);
}

int		player_move(char **map, t_obj **objs, t_player *plr)
{
	char	ch;

	ch = getch();
	if (ch == 'w' && player_collision(map, objs, plr, plr->y-1, plr->x))
		plr->y -= 1;
	else if (ch == 's' && player_collision(map, objs, plr, plr->y+1, plr->x))
		plr->y += 1;
	else if (ch == 'a' && player_collision(map, objs, plr, plr->y, plr->x-1))
		plr->x -= 1;
	else if (ch == 'd' && player_collision(map, objs, plr, plr->y, plr->x+1))
		plr->x += 1;
	else if (ch == 'e')
		object_act(objs, plr);
	else if (ch == 'q')
		return (0);
	return (1);
}
