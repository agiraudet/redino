/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 02:35:47 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 21:15:41 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void	obj_portal_act(t_obj *self, t_player *plr)
{
	(void)self;
	(void)plr;
}

int		obj_portal_coll(t_obj *self, t_player *plr)
{
	plr->color = self->color;
	return (1);
}

void	obj_portal_update(t_obj *self)
{
	(void)self;
}

void	obj_portal_init_fct(t_ctl *ctl, int fct)
{
	if (fct & 4)
		ctl->act = &obj_portal_act;
	if (fct & 2)
		ctl->coll = &obj_portal_coll;
	if (fct & 1)
		ctl->update = &obj_portal_update;
}
