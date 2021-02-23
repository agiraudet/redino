/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:14:47 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/23 17:02:45 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

SDL_Texture	*scene_tex_load(SDL_Renderer *renderer, const char *path)
{
	SDL_Texture	*tex;
	SDL_Surface	*surf;
	int			r, g, b;

	surf = SDL_LoadBMP(path);
	if (!surf)
		return (0);
	hex_to_rgb(COLOR_KEY, &r, &g, &b);
	SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, r ,g ,b));
	tex = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	return (tex);
}

void		scene_destroy(t_scene *sc)
{
	SDL_DestroyRenderer(sc->ren);
	SDL_DestroyWindow(sc->win);
	SDL_DestroyTexture(sc->atlas);
	TTF_CloseFont(sc->font);
	SDL_Quit();
	TTF_Quit();
	free(sc);
	sc = 0;
}

t_scene		*scene_create(char *title, int wd, int hg, const char *atlas_path)
{
	t_scene *sc;

	if (SDL_INIT_VIDEO < 0)
		return (0);
	if (TTF_Init() < 0)
	{
		SDL_Quit();
		return (0);
	}
	if (!(sc = malloc(sizeof(t_scene))))
	{
		SDL_Quit();
		return (0);
	}
	SDL_CreateWindowAndRenderer(wd, hg, SDL_WINDOW_SHOWN, &sc->win, &sc->ren);
	if (!sc->win || !sc->ren)
	{
		SDL_Quit();
		free(sc);
		return (0);
	}
	SDL_SetWindowTitle(sc->win, title);
	sc->atlas = scene_tex_load(sc->ren, atlas_path);
	if (!sc->atlas)
	{
		SDL_DestroyRenderer(sc->ren);
		SDL_DestroyWindow(sc->win);
		SDL_Quit();
		free(sc);
		return (0);
	}
	sc->font = text_font_load(FONT_PATH, FONT_SIZE);
	sc->wd = wd;
	sc->hg = hg;
	timer_init(&sc->time);
	return (sc);
}
