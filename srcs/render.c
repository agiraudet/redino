/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:03:15 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 17:20:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

t_resolution	g_res;

void	get_map_maxyx(char **map, int *hg, int *wd)
{
	int		i;
	int		len;
	int		max_len;

	i = 0;
	max_len = 0;
	while (map[i])
	{
		len = strlen(map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	*hg = i;
	*wd = max_len;
}

void	render_set_res(char **map)
{
	g_res.hg = 0;
	g_res.wd = 0;
	g_res.map_hg = 0;
	g_res.map_wd = 0;
	getmaxyx(stdscr, g_res.hg, g_res.wd);
	get_map_maxyx(map, &g_res.map_hg, &g_res.map_wd);
	g_res.off_y = (g_res.hg - g_res.map_hg) / 2;
	g_res.off_x = (g_res.wd - g_res.map_wd) / 2;
}

void	render_one_egg(t_egg *egg)
{
		attron(COLOR_PAIR(egg->color));
		mvprintw(egg->y + g_res.off_y, egg->x + g_res.off_x, "e");
		attroff(COLOR_PAIR(egg->color));
		refresh();
}

void	render_egg(t_player *plr)
{
	int		i;

	i = plr->egc - 1;
	while (i >= 0)
	{
		attron(COLOR_PAIR(plr->egg[i].color));
		mvprintw(plr->egg[i].y + g_res.off_y, plr->egg[i].x + g_res.off_x, "e");
		attroff(COLOR_PAIR(plr->egg[i].color));
		i--;
	}
}

void	render_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		attron(A_DIM);
		mvwprintw(stdscr, i + g_res.off_y, g_res.off_x, "%s", map[i]);
		attroff(A_DIM);
		i++;
	}
}

void	render_objs(t_obj *objs)
{
	while (objs)
	{
		attron(COLOR_PAIR(objs->color));
		mvprintw(objs->y + g_res.off_y, objs->x + g_res.off_x, objs->pch);
		attroff(COLOR_PAIR(objs->color));
		objs = objs->next;
	}
}

void	render_player(t_player *plr)
{
	
	attron(A_BOLD | COLOR_PAIR(plr->color));
	mvprintw(plr->y + g_res.off_y, plr->x + g_res.off_x, plr->chr);
	attroff(A_BOLD | COLOR_PAIR(plr->color));
}

void	render_level(t_level *lvl)
{
	render_map(lvl->map);
	render_objs(lvl->objs);
	render_egg(lvl->plr);
	render_player(lvl->plr);
	if (lvl->hint)
		ux_print_hint(lvl->hint);
	if (lvl->name)
		ux_print_name(lvl->name);
	refresh();
}

void	render_clean_screen(void)
{
	erase();
}
