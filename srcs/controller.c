/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:35:48 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 00:28:51 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		ctl_obj_is_parent(t_obj *self, t_obj *obj)
{
	if (obj == self)
		return (0);
	if (!obj->ctl)
		return (0);
	if (!obj->ctl->sensor)
		return (0);
	if (obj->ctl->group != self->ctl->group)
		return (0);
	return (1);
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
		if (ctl_obj_is_parent(self, objs))
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
		if (ctl_obj_is_parent(self, objs))
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
