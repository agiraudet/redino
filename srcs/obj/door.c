/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:42:58 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 17:36:09 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		obj_door_coll(t_obj *self, t_player *plr)
{
	(void)plr;
	if (self->status == ACT)
	{
		win();
		return (1);
	}
	else
		return (0);
}

void	obj_door_update(t_obj *self)
{
	int		i;
	int		parent_up;

	i = 0;
	parent_up = 0;
	while (self->ctl->parent[i])
		if (self->ctl->parent[i++]->status == ACT)
			parent_up++;
	if (self->ctl->logic(parent_up, i) == 1)
	{
		self->status = ACT;
		self->color = BG_WHITE;
	}
	else
	{
		self->status = DEACT;
		self->color = BG_BLACK;
	}
}
