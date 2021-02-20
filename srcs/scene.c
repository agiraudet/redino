/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:24:30 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/20 10:38:23 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void	scene_fill_bg(t_scene *sc, int hex)
{
	int		r;
	int		g;
	int		b;

	r = (hex >> 16) & 0xFF;
	g = (hex >> 8) & 0xFF;
	b = hex & 0xFF;
	SDL_FillRect(sc->surf, 0, SDL_MapRGB(sc->surf->format, r, g, b));
}

void	scene_destroy(t_scene *sc)
{
	if (sc->atlas)
		SDL_FreeSurface(sc->atlas);
	if (sc->tmp_surf)
		SDL_FreeSurface(sc->tmp_surf);
	if (sc->win)
		SDL_DestroyWindow(sc->win);
	SDL_Quit();
	free(sc);
}

int		scene_load_atlas(t_scene *sc, char *atlas_path)
{
	SDL_Surface	*tmp;
	tmp = SDL_LoadBMP(atlas_path);
	if (!tmp)
	{
		printf("SDL Atlas loading Error: %s\n", SDL_GetError());
		return (0);
	}
	sc->atlas = SDL_ConvertSurface(tmp, sc->surf->format, 0);
	SDL_SetColorKey(sc->atlas, SDL_TRUE, COLOR_KEY);
	SDL_FreeSurface(tmp);
	return (1);
}

int		scene_set_tmp_surf(t_scene *sc, t_level *lvl)
{
	SDL_Surface	*tmp;

	if (sc->tmp_surf)
		SDL_FreeSurface(sc->tmp_surf);
	tmp = SDL_CreateRGBSurface(0, lvl->map_size_x, lvl->map_size_y, 32, 0, 0, 0, 0);
	if (!tmp)
	{
		free(sc);
		return (0);
	}
	sc->tmp_surf = SDL_ConvertSurface(tmp, sc->surf->format, 0);
	SDL_SetColorKey(sc->tmp_surf, SDL_TRUE, COLOR_KEY);
	SDL_FreeSurface(tmp);
	if (!sc->tmp_surf)
	{
		free(sc);
		return (0);
	}
	return (1);
}

t_scene		*scene_create(char *title, int wd, int hg)
{
	t_scene		*sc;

	if (!(sc = malloc(sizeof(t_scene))))
		return (0);
	sc->win = 0;
	sc->surf = 0;
	sc->atlas = 0;
	sc->wd = wd;
	sc->hg = hg;
	sc->tmp_surf = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_INIT_VIDEO Error: %s\n", SDL_GetError());
		free(sc);
		return (0);
	}
	sc->win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wd, hg, SDL_WINDOW_SHOWN);
	if (!sc->win)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		free(sc);
		SDL_Quit();
		return (0);
	}
	sc->surf = SDL_GetWindowSurface(sc->win);
	SDL_FillRect(sc->surf, 0, SDL_MapRGB(sc->surf->format, 0, 0, 0));
	return (sc);
}

void	scene_gen_sprite(SDL_Rect *sprite, int sprite_nb)
{
	sprite->x = (sprite_nb * SPRITE_SIZE) % ATLAS_SIZE;
	sprite->y = (sprite_nb * SPRITE_SIZE) / ATLAS_SIZE * SPRITE_SIZE;
	sprite->w = SPRITE_SIZE;
	sprite->h = SPRITE_SIZE;
}


void	scene_blit_sprite_color(t_scene *sc, SDL_Rect *sprite, SDL_Rect *dest, int hex)
{
	SDL_Surface	*tmp1;
	SDL_Surface	*tmp2;
	int			r, g, b;

	r = (hex >> 16) & 0xFF;
	g = (hex >> 8) & 0xFF;
	b = hex & 0xFF;
	tmp1 = SDL_CreateRGBSurface(0, SPRITE_SIZE, SPRITE_SIZE, 32, 0,0,0,0);
	tmp2 = SDL_ConvertSurface(tmp1, sc->surf->format, 0);
	SDL_SetColorKey(tmp2, SDL_TRUE, COLOR_KEY);
	SDL_SetColorKey(sc->atlas, SDL_FALSE, COLOR_KEY);
	SDL_BlitScaled(sc->atlas, sprite, tmp2, 0);
	SDL_SetSurfaceColorMod(tmp2, r, g ,b);
	SDL_BlitSurface(tmp2, 0, sc->tmp_surf, dest);
	SDL_SetColorKey(sc->atlas, SDL_TRUE, COLOR_KEY);
	SDL_FreeSurface(tmp1);
	SDL_FreeSurface(tmp2);
}

void	scene_blit_sprite(t_scene *sc, int sprite_nb, int x, int y, int hex)
{

	SDL_Rect	sprite;
	SDL_Rect	dest;

	if (sprite_nb < 0)
		return ;
	scene_gen_sprite(&sprite, sprite_nb);
	dest.x = (x * SPRITE_SIZE);
	dest.y = (y * SPRITE_SIZE);
	dest.w = SPRITE_SIZE;
	dest.h = SPRITE_SIZE;
	if (hex >=  0)
	{
		scene_blit_sprite_color(sc, &sprite, &dest, hex);
	}
	else
		SDL_BlitSurface(sc->atlas, &sprite, sc->tmp_surf, &dest);
}

void	scene_update(t_scene *sc)
{
	SDL_BlitScaled(sc->tmp_surf, 0, sc->surf, &sc->offset);
	SDL_UpdateWindowSurface(sc->win);
}

int		scene_get_sprite_nb(char c)
{
	if (c == 'w')
		return (WALL_SPRITE);
	if (c == '.')
		return (GROUND_SPRITE);
	return (-1);
}

void	scene_set_offset(t_scene *sc, t_level *lvl)
{
	int		virt_wd;
	int		virt_hg;

	virt_wd = sc->wd - MARGIN * 2;
	virt_hg = sc->hg - MARGIN * 2;

	if (virt_wd % lvl->map_size_x > virt_hg % lvl->map_size_y)
	{
		sc->offset.h = virt_hg;
		sc->offset.y = MARGIN;
		sc->offset.w = lvl->map_size_x * (virt_hg / lvl->map_size_y);
		sc->offset.x = (sc->wd - sc->offset.w) / 2;
	}
	else
	{
		sc->offset.w = virt_wd;
		sc->offset.x = MARGIN;
		sc->offset.h = lvl->map_size_y * (virt_wd / lvl->map_size_x);
		sc->offset.y = (sc->hg - sc->offset.w) / 2;
	}
}
