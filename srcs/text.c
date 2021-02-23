/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:59:13 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/23 15:54:26 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void		text_txt_destroy(t_txt *txt)
{
	t_txt	*tmp;
	while (txt)
	{
		tmp = txt;
		free(txt->name);
		txt = txt->next;
		free(tmp);
	}
}

void		text_manager_destroy(t_text_manager *tm)
{
	TTF_CloseFont(tm->font);
	text_txt_destroy(tm->txt);
	free(tm);
	tm = 0;
}

TTF_Font	*text_font_load(const char *font_path, int font_size)
{
	TTF_Font	*font;

	font = TTF_OpenFont(font_path, font_size);
	if (!font)
	{
		printf("Error: %s\n", TTF_GetError());
		return (0);
	}
	return (font);
}

t_txt		*text_txt_create(t_scene *sc, t_text_manager *tm, const char *str, int hex)
{
	t_txt		*txt;
	SDL_Surface	*surf;
	SDL_Color	color;

	hex_to_sdl_color(hex, &color);
	txt = malloc(sizeof(t_txt));
	if (!txt)
		return (0);
	surf = TTF_RenderText_Solid(tm->font, str, color);
	if (!surf)
	{
		printf("Font error: %s\n", SDL_GetError());
		return (0);
	}
	txt->tex = SDL_CreateTextureFromSurface(sc->ren, surf);
	if (!txt->tex)
	{
		printf("Font error: %s\n", SDL_GetError());
		return (0);
	}
	txt->dest.w = surf->w;
	txt->dest.h = surf->h;
	txt->dest.x = 0;
	txt->dest.y = 0;
	txt->pos = TXT_CENTER;
	txt->name = strdup(str);
	SDL_FreeSurface(surf);
	return (txt);
}

void		text_txt_add(t_scene *sc, t_text_manager *tm, const char *str, int hex)
{
	t_txt	*txt;

	txt = text_txt_create(sc, tm, str, hex);
	txt->next = tm->txt;
	tm->txt = txt;
}

void	text_txt_add_multiple(t_scene *sc, t_text_manager *tm, char **strs, int hex)
{
	int		i;

	i = 0;
	while (strs[i])
		text_txt_add(sc, tm, strs[i++], hex);
}

t_text_manager	*text_manager_create(const char *font_path, int font_size)
{
	t_text_manager	*tm;

	tm = malloc(sizeof(t_text_manager));
	if (!tm)
		return (0);
	tm->font = text_font_load(font_path, font_size);
	tm->txt = 0;
	return (tm);
}

void			text_manager_init_pos_x(t_scene *sc, t_text_manager *tm)
{
	t_txt	*txt;

	txt = tm->txt;
	while (txt)
	{
		if (txt->pos == TXT_CENTER)
			txt->dest.x = (sc->wd - txt->dest.w) / 2;
		txt = txt->next;
	}
}
