/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:21:04 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/21 17:36:37 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		main(int argc, char **argv)
{
	t_scene		*sc;

	if (!(sc = scene_create(TITLE, WIN_WD, WIN_HG, ATLAS_PATH)))
		return (1);
	if (argc > 1)
		play_one_level(sc, argv[1]);
	else
		play_all_level(sc, LEVEL_PATH);
	scene_destroy(sc);
	return (0);
}
