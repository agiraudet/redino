/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:35:48 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 19:22:07 by agiraude         ###   ########.fr       */
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

int		ctl_count_parent(t_obj *self, t_obj *objs)
{
	int		nb_parent;

	nb_parent = 0;
	while (objs)
	{
		if (objs->ctl && objs->ctl->group == self->ctl->group && objs != self)
			nb_parent++;
		objs = objs->next;
	}
	return (nb_parent);
}

t_obj	**ctl_build_parent(t_obj *self, t_obj *objs)
{
	t_obj	**parent;
	int		nb_parent;
	int		i;

	nb_parent = ctl_count_parent(self, objs);
	if (!(parent = malloc(sizeof(t_obj*) * (nb_parent + 1))))
		return (0);
	i = 0;
	while (objs)
	{
		if (objs->ctl && objs->ctl->group == self->ctl->group && objs != self)
			parent[i++] = objs;
		objs = objs->next;
	}
	parent[i] = 0;
	return (parent);
}

void	ctl_build_all(t_obj *objs)
{
	t_obj	*obj_list;

	obj_list = objs;
	while (objs)
	{
		if (objs->ctl && objs->ctl->group != 0)
			objs->ctl->parent = ctl_build_parent(objs, obj_list);
		objs = objs->next;
	}
}
