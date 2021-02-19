/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:03:15 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 01:31:05 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void	render_one_egg(t_egg *egg)
{
		attron(COLOR_PAIR(egg->color));
		mvprintw(egg->y, egg->x, "e");
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
		mvprintw(plr->egg[i].y, plr->egg[i].x, "e");
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
		mvwprintw(stdscr, i, 0, "%s", map[i]);
		attroff(A_DIM);
		i++;
	}
}

void	render_objs(t_obj *objs)
{
	while (objs)
	{
		attron(COLOR_PAIR(objs->color));
		mvprintw(objs->y, objs->x, objs->chr);
		attroff(COLOR_PAIR(objs->color));
		objs = objs->next;
	}
}

void	render_player(t_player *plr)
{
	attron(A_BOLD | COLOR_PAIR(plr->color));
	mvprintw(plr->y, plr->x, plr->chr);
	attroff(A_BOLD | COLOR_PAIR(plr->color));
}

void	render_level(t_level *lvl)
{
	render_map(lvl->map);
	render_objs(lvl->objs);
	render_egg(lvl->plr);
	render_player(lvl->plr);
	refresh();
}
