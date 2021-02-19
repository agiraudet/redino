/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:21:04 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 18:40:41 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		main(int argc, char **argv)
{
	init_ncurse();
	ux_init();
	ux_title_screen();
	if (argc > 1)
		play_solo_lvl(argv[1]);
	else
		play_all_lvl("levels/");
	endwin();
	return (0);
}
