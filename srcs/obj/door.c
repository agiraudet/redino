/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:42:58 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 21:19:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void	obj_door_act(t_obj *self, t_player *plr)
{
	(void)self;
	(void)plr;
}

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

void	obj_door_init_fct(t_ctl *ctl, int fct)
{
	if (fct & 4)
		ctl->act = &obj_door_act;
	if (fct & 2)
		ctl->coll = &obj_door_coll;
	if (fct & 1)
		ctl->update = &obj_door_update;
}
