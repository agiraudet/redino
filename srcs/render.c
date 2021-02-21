/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:33:45 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/21 18:45:22 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		g_offset_x = 0;
int		g_offset_y = 0;

void	render_set_offset(t_scene *sc, t_level *lvl)
{
	g_offset_x = (sc->wd - lvl->map_size_x * SPRITE_SIZE * SCALE) / 2;
	g_offset_y = (sc->hg - lvl->map_size_y * SPRITE_SIZE * SCALE) / 2;
}

void	render_gen_sprite(SDL_Rect *sprite, int sprite_nb)
{
	sprite->x = (sprite_nb * SPRITE_SIZE) % ATLAS_SIZE;
	sprite->y = (sprite_nb * SPRITE_SIZE) / ATLAS_SIZE * SPRITE_SIZE;
	sprite->w = SPRITE_SIZE;
	sprite->h = SPRITE_SIZE;
}

void	render_sprite(t_scene *sc, int sprite_nb, int x, int y)
{
	SDL_Rect	dest;
	SDL_Rect	sprite;

	dest.x = x * SPRITE_SIZE * SCALE + g_offset_x;
	dest.y = y * SPRITE_SIZE * SCALE + g_offset_y;
	dest.w = SPRITE_SIZE * SCALE;
	dest.h = SPRITE_SIZE * SCALE;
	render_gen_sprite(&sprite, sprite_nb);
	SDL_RenderCopy(sc->ren, sc->atlas, &sprite, &dest);
}

void	render_map(t_scene *sc, char **map)
{
	int		x;
	int		y;
	int		sprite_nb;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			sprite_nb = -1;
			if (map[y][x] == 'w')
				sprite_nb = 0;
			else if (map[y][x] == '.')
				sprite_nb = 1;
			if (sprite_nb != -1)
				render_sprite(sc, sprite_nb, x, y);
			x++;
		}
		y++;
	}
}

void	render_objs(t_scene *sc, t_obj *objs)
{
	int		r, g, b;

	while (objs)
	{
		hex_to_rgb(objs->color, &r, &g, &b);
		SDL_SetTextureColorMod(sc->atlas, r, g, b);
		render_sprite(sc, objs->sprite[objs->frame], objs->x, objs->y);
		SDL_SetTextureColorMod(sc->atlas, 0xFF, 0xFF, 0xFF);
		objs = objs->next;
	}
}

void	render_egg(t_scene *sc, t_player *plr)
{
	int		i;
	int		r, g, b;

	i = plr->egc - 1;
	while (i >= 0)
	{
		hex_to_rgb(plr->color, &r, &g, &b);
		SDL_SetTextureColorMod(sc->atlas, r, g, b);
		render_sprite(sc, plr->sprite_egg[plr->egg[i].frame], plr->egg[i].x, plr->egg[i].y);
		SDL_SetTextureColorMod(sc->atlas, 0xFF, 0xFF, 0xFF);
		i--;
	}
}

void	render_player(t_scene *sc, t_player *plr)
{
	int		r, g, b;

	hex_to_rgb(plr->color, &r, &g, &b);
	SDL_SetTextureColorMod(sc->atlas, r, g, b);
	render_sprite(sc, plr->sprite[plr->frame], plr->x, plr->y);
	SDL_SetTextureColorMod(sc->atlas, 0xFF, 0xFF, 0xFF);
}

void	render_level(t_scene *sc, t_level *lvl)
{
	SDL_SetRenderDrawColor(sc->ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(sc->ren);
	render_map(sc, lvl->map);
	render_objs(sc, lvl->objs);
	render_egg(sc, lvl->plr);
	render_player(sc ,lvl->plr);
	SDL_RenderPresent(sc->ren);
}
