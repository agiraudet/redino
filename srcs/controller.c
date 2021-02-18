/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:35:48 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 17:28:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

t_ctl	*ctl_create
	(void (*act)(t_obj*, t_player *plr), 
	 int (*coll)(t_obj*, t_player*),
	 int (*logic)(int, int),
	 void (*update)(t_obj*),
	 int group)
{
	t_ctl	*ctl;

	if (!(ctl = malloc(sizeof(t_ctl))))
		return (0);
	ctl->act = act;
	ctl->coll = coll;
	ctl->logic = logic;
	ctl->update = update;
	ctl->group = group;
	ctl->parent = 0;
	return (ctl);
}

void	ctl_destroy(t_ctl *ctl)
{
	if (ctl->parent)
		free(ctl->parent);
	free(ctl);
}

t_obj	**ctl_build_parent(t_obj *self, t_obj **objs)
{
	t_obj **ret;
	int		i;
	int		nb_parent;

	i = 0;
	nb_parent = 0;
	while (objs[i])
	{
		if (objs[i]->ctl)
			if (objs[i]->ctl->group == self->ctl->group)
				if (objs[i] != self)
					nb_parent++;
		i++;
	}
	if (!(ret = malloc(sizeof(t_obj*))))
		return (0);
	i = 0;
	nb_parent = 0;
	while (objs[i])
	{
		if (objs[i]->ctl)
			if (objs[i]->ctl->group == self->ctl->group)
				if (objs[i] != self)
					ret[nb_parent++] = objs[i];
		i++;
	}
	ret[nb_parent] = 0;
	return (ret);
}

void	ctl_build_all(t_obj **objs)
{
	int		i;

	i = 0;
	while (objs[i])
	{
		if (objs[i]->ctl && objs[i]->ctl->group != 0)
			objs[i]->ctl->parent = ctl_build_parent(objs[i], objs);
		i++;
	}
}
