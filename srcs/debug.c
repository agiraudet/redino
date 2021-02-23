/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:15:57 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/22 19:27:54 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void		debug_hitbox(t_scene *sc, SDL_Rect *dest)
{
	SDL_Rect	box;

	box.x = plr->x
	SDL_SetRenderDrawColor(sc->ren, 0xFF, 0x0, 0x0, 0x0);
	SDL_RenderDrawRect(sc->ren, dest);
}
