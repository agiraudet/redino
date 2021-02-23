/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:33:45 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/23 15:51:13 by agiraude         ###   ########.fr       */
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

void	render_text_init_pos_y(t_scene *sc, t_level *lvl)
{
	t_txt	*txt;

	txt = lvl->tm->txt;
	while (txt)
	{
		txt->dest.y = sc->hg - g_offset_y / 2 - txt->dest.h / 2;
		txt = txt->next;
	}
}

void	render_gen_sprite(SDL_Rect *sprite, int sprite_nb)
{
	sprite->x = (sprite_nb * SPRITE_SIZE) % ATLAS_SIZE;
	sprite->y = (sprite_nb * SPRITE_SIZE) / ATLAS_SIZE * SPRITE_SIZE;
	sprite->w = SPRITE_SIZE;
	sprite->h = SPRITE_SIZE;
}

void	render_gen_dest(SDL_Rect *dest, double x, double y)
{
	dest->x = (int)x * SPRITE_SIZE * SCALE + g_offset_x;
	dest->x += (x - (int)x) * SPRITE_SIZE * SCALE;
	dest->y = (int)y * SPRITE_SIZE * SCALE + g_offset_y;
	dest->y += (y - (int)y) * SPRITE_SIZE * SCALE;
	dest->w = SPRITE_SIZE * SCALE;
	dest->h = SPRITE_SIZE * SCALE;
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

void	render_player(t_scene *sc, t_player *plr)
{
	SDL_Rect	dest;
	SDL_Rect	sprite;
	int			r, g, b;

	hex_to_rgb(plr->color, &r, &g, &b);
	SDL_SetTextureColorMod(sc->atlas, r, g, b);
	render_gen_dest(&dest, plr->x, plr->y);
	render_gen_sprite(&sprite, plr->sprite[plr->frame]);
	SDL_RenderCopy(sc->ren, sc->atlas, &sprite, &dest);
	SDL_SetTextureColorMod(sc->atlas, 0xFF, 0xFF, 0xFF);
}

void	render_egg(t_scene *sc, t_player *plr)
{
	SDL_Rect	sprite;
	SDL_Rect	dest;
	int		i;

	i = 0;
	while (i < plr->egc)
	{
		render_gen_dest(&dest, plr->egg[i].x, plr->egg[i].y);
		render_gen_sprite(&sprite, plr->sprite_egg[plr->frame]);
		SDL_RenderCopy(sc->ren, sc->atlas, &sprite, &dest);
		i++;
	}
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
				sprite_nb = 1;
			else if (map[y][x] == '.')
				sprite_nb = 0;
			else if (map[y][x] == 'W')
				sprite_nb = 11;
			if (sprite_nb != -1)
				render_sprite(sc, sprite_nb, x, y);
			x++;
		}
		y++;
	}
}

int		render_objs(t_scene *sc, t_obj *objs, t_player *plr)
{
	int		player_behind;
	int		r, g, b;

	player_behind = 0;
	while (objs)
	{
		if (player_behind_obj(plr, objs))
				player_behind = 1;
		hex_to_rgb(objs->color, &r, &g, &b);
		SDL_SetTextureColorMod(sc->atlas, r, g, b);
		render_sprite(sc, objs->sprite[objs->frame], objs->x, objs->y);
		SDL_SetTextureColorMod(sc->atlas, 0xFF, 0xFF, 0xFF);
		objs = objs->next;
	}
	return (player_behind);
}

void	render_text(t_scene *sc, t_text_manager *tm)
{
	t_txt		*txt;

	txt = tm->txt;
	while (txt)
	{
		SDL_RenderCopy(sc->ren, txt->tex, 0, &txt->dest);
		txt = txt->next;
	}
}

void	render_text_variable(t_scene *sc, t_text_manager *tm, char *str)
{
	t_txt	*txt;

	txt = text_txt_create(sc, tm, str, WHITE);
	txt->dest.x = 10;
	txt->dest.y = 10;
	SDL_RenderCopy(sc->ren, txt->tex, 0, &txt->dest);
	text_txt_destroy(txt);
	free(str);
}


void	render_level(t_scene *sc, t_level *lvl)
{
	SDL_SetRenderDrawColor(sc->ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(sc->ren);
	render_map(sc, lvl->map);
	render_egg(sc, lvl->plr);
	render_player(sc ,lvl->plr);
	if (!render_objs(sc, lvl->objs, lvl->plr))
		render_player(sc ,lvl->plr);
	render_text(sc, lvl->tm);
	if (DEBUG_FPS)
		render_text_variable(sc, lvl->tm, ft_u32toa(timer_get_fps(&sc->time)));
	SDL_RenderPresent(sc->ren);
	timer_cap_fps(&sc->time);
}
