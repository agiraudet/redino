/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lever.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:35:33 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 15:31:07 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void	obj_lever_act(t_obj *self, t_player *plr)
{
	if (self->x == plr->x && self->y == plr->y && self->color == plr->color)
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

void	obj_lever_update(t_obj *self)
{
	if (self->status == ACT)
		self->chr = "/";
	else
		self->chr = "\\";
}
