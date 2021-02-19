/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:24:30 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 22:52:09 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

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
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_INIT_VIDEO Error: %s\n", SDL_GetError());
		return (0);
	}
	sc->win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wd, hg, SDL_WINDOW_SHOWN);
	if (!sc->win)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (0);
	}
	sc->surf = SDL_GetWindowSurface(sc->win);
	return (sc);
}

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
	{
		SDL_FreeSurface(sc->atlas);
		sc->atlas = 0;
	}
	if (sc->win)
	{
		SDL_DestroyWindow(sc->win);
		sc->win = 0;
		sc->surf = 0;
	}
	SDL_Quit();
	free(sc);
}

int		scene_load_atlas(t_scene *sc, char *atlas_path)
{
	sc->atlas = SDL_LoadBMP(atlas_path);
	if (!sc->atlas)
	{
		printf("SDL Atlas loading Error: %s\n", SDL_GetError());
		return (0);
	}
	return (1);
}

void	scene_gen_sprite(SDL_Rect *sprite, int sprite_nb)
{
	sprite->x = (sprite_nb * SPRITE_SIZE) % ATLAS_SIZE;
	sprite->y = (sprite_nb * SPRITE_SIZE) / ATLAS_SIZE * SPRITE_SIZE;
	sprite->w = SPRITE_SIZE;
	sprite->h = SPRITE_SIZE;
}

void	scene_blit_sprite(t_scene *sc, int sprite_nb, int x, int y)
{
	SDL_Rect	sprite;
	SDL_Rect	dest;

	if (sprite_nb < 0)
		return ;
	scene_gen_sprite(&sprite, sprite_nb);
	dest.x = x;
	dest.y = y;
	dest.w = SPRITE_SIZE;
	dest.h = SPRITE_SIZE;
	SDL_BlitSurface(sc->atlas, &sprite, sc->surf, &dest);
}

int		scene_get_sprite_nb(char c)
{
	if (c == 'w')
		return (1);
	if (c == '.')
		return (0);
	return (-1);
}

void	scene_center_map(t_scene *sc, char **map, int *off_x, int *off_y)
{
	int		size_x;
	int		loc_x;
	int		size_y;

	size_x = 0;
	size_y = 0;
	while (map[size_y])
	{
		loc_x = 0;
		while (map[size_y][loc_x])
			loc_x++;
		if (size_x < loc_x)
			size_x = loc_x;
		size_y++;
	}
	size_x *= SPRITE_SIZE;
	size_y *= SPRITE_SIZE;
	*off_x = (sc->wd - size_x) / 2;
	*off_y = (sc->hg - size_y) / 2;
}

void	scene_blit_map(t_scene *sc, char **map)
{
	int		y;
	int		x;
	int		off_y;
	int		off_x;

	scene_center_map(sc, map, &off_x, &off_y);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			scene_blit_sprite(sc, scene_get_sprite_nb(map[y][x]), x * SPRITE_SIZE + off_x, y * SPRITE_SIZE + off_y);
			x++;
		}
		y++;
	}
}
