/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 00:52:14 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 01:47:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		egg_check_pos(t_player *plr)
{
	int		i;

	i = plr->egc - 1;
	while (i >= 0)
	{
		if (plr->egg[i].x == plr->x && plr->egg[i].y == plr->y)
			return (0);
		i--;
	}
	return (1);
}

int		egg_drop(t_player *plr)
{
	if (plr->egc < plr->max_egg && egg_check_pos(plr))
	{
		plr->egg[plr->egc].x = plr->x;
		plr->egg[plr->egc].y = plr->y;
		plr->egg[plr->egc].color = plr->color;
		plr->egc++;
		return (1);
	}
	return (0);
}

void	egg_hatch(t_player *plr)
{
	if (plr->egc > 0)
	{
		plr->x = plr->egg[plr->egc - 1].x;
		plr->y = plr->egg[plr->egc - 1].y;
		plr->color =  plr->egg[plr->egc - 1].color;
		plr->egc--;
	}
}
