/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spike.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:01:13 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 21:48:53 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void	obj_spike_act(t_obj *self, t_player *plr)
{
	(void)self;
	(void)plr;
}

int		obj_spike_coll(t_obj *self, t_player *plr)
{
	if (self->color == plr->color)
		return (1);
	else
		return (0);
}

void	obj_spike_update(t_obj *self)
{
	(void)self;
}

void	obj_spike_init_fct(t_ctl *ctl, int fct)
{
	if (fct & 4)
		ctl->act = &obj_spike_act;
	if (fct & 2)
		ctl->coll = &obj_spike_coll;
	if (fct & 1)
		ctl->update = &obj_spike_update;
}
