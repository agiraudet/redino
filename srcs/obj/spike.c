/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spike.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:01:13 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 14:37:28 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		obj_spike_coll(t_obj *self, t_player *plr)
{
	if (self->color == plr->color)
		return (1);
	else
		return (0);
}
