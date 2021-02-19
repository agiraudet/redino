/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lever.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:35:33 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 17:01:18 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void	obj_lever_act(t_obj *self, t_player *plr)
{
	if (player_is_near(self, plr) && self->color == plr->color)
	{
		if (self->status == ACT)
		{
			self->status = DEACT;
		}
		else
		{
			self->status = ACT;
		}
	}
}

int		obj_lever_coll(t_obj *self, t_player *plr)
{
	(void)self;
	(void)plr;
	return (1);
}

void	obj_lever_update(t_obj *self)
{
	if (self->status == ACT)
		self->pch[0] = self->chr[0];
	else
		self->pch[0] = self->chr[1];
}

void	obj_lever_init_fct(t_ctl *ctl, int fct)
{
	if (fct & 4)
		ctl->act = &obj_lever_act;
	if (fct & 2)
		ctl->coll = &obj_lever_coll;
	if (fct & 1)
		ctl->update = &obj_lever_update;
}
