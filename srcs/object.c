/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:45:29 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/22 00:14:44 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void	object_add(t_obj **obj_lst, t_obj *obj)
{
	obj->next = *obj_lst;
	*obj_lst = obj;
}

void	object_destroy(t_obj *obj)
{
	if (obj->ctl)
		ctl_destroy(obj->ctl);
	free(obj->sprite);
	free(obj);
}

void	object_update(t_obj *obj_lst)
{
	while (obj_lst)
	{
		if (obj_lst->ctl && obj_lst->ctl->update)
			obj_lst->ctl->update(obj_lst);
		obj_lst = obj_lst->next;
	}
}

void	object_act(t_obj *obj_lst, t_player *plr)
{
	while (obj_lst)
	{
		if (obj_lst->ctl && obj_lst->ctl->act)
		{
			obj_lst->ctl->act(obj_lst, plr);
		}
		obj_lst = obj_lst->next;
	}
}
