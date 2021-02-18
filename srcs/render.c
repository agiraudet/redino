/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:03:15 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 17:37:00 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

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

void	render_objs(t_obj **objs)
{
	int		i;

	i = 0;
	while (objs[i])
	{
		attron(COLOR_PAIR(objs[i]->color));
		mvprintw(objs[i]->y, objs[i]->x, objs[i]->chr);
		attroff(COLOR_PAIR(objs[i]->color));
		i++;
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
	render_player(lvl->plr);
	refresh();
}
