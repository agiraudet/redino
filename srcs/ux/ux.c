/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ux.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:49:22 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 17:22:55 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

extern t_resolution	g_res;

void	ux_print_middle(int y, char *str, int color, int bold)
{
	int		len;
	int		off;

	len = strlen(str);
	off = (g_res.wd - len) / 2;
	if (bold)
		attron(A_BOLD);
	attron(COLOR_PAIR(color));
	mvwprintw(stdscr, y, off, "%s", str);
	attroff(COLOR_PAIR(color));
	if (bold)
		attroff(A_BOLD);
}

void	ux_print_title(void)
{
	int		y_off;
	int		title_size;

	title_size = 10;
	y_off = (g_res.hg - title_size) / 2;
	ux_print_middle(y_off, "REDINO", WHITE, 1);
	ux_print_middle(y_off + 2, "- press any key to start -", WHITE, 0);
	ux_print_middle(y_off + 4, "h - help", WHITE, 0);
	ux_print_middle(y_off + 5, "q - quit", WHITE, 0);
}

void	ux_print_hint(char *str)
{
	int		x;
	int		y;

	if (!str)
		return ;
	x = (g_res.wd - strlen(str)) / 2;
	y = g_res.off_y + g_res.map_hg + 2;
	mvwprintw(stdscr, y, x, "%s", str);
}

void	ux_print_name(char *str)
{
	int		x;
	int		y;

	x = (g_res.wd - strlen(str)) / 2;
	y = g_res.off_y - 2;
	attron(A_BOLD);
	mvwprintw(stdscr, y, x, "%s", str);
	attroff(A_BOLD);
}

void	ux_title_screen(void)
{
	char	chr;

	ux_print_title();
	refresh();
	chr = getch();
	render_clean_screen();
	if (chr == 'q')
	{
		endwin();
		exit(0);
	}
}

void	ux_init(void)
{
	getmaxyx(stdscr, g_res.hg, g_res.wd);
}
