/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:00:09 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/18 17:39:20 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void		colors_init(void)
{
	init_pair(WHITE, COLOR_WHITE, -1);
	init_pair(RED, COLOR_RED, -1);
	init_pair(GREEN, COLOR_GREEN, -1);
	init_pair(BLUE, COLOR_BLUE, -1);
	init_pair(BG_WHITE, COLOR_WHITE, COLOR_WHITE);
	init_pair(BG_BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(NONE, -1, -1);
}

void		init_ncurse(void)
{
	initscr();
	noecho();
	curs_set(0);
	start_color();
	use_default_colors();
	colors_init();
}
