/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:21:04 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/20 05:24:25 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

int		main()
{
	t_scene		*sc;

	if (!(sc = scene_create("redino", 640, 480)))
		return (1);
	if (!(scene_load_atlas(sc, "assets/atlas.bmp")))
	{
		scene_destroy(sc);
		return (1);
	}
	play_all_level(sc, "levels/");
	scene_destroy(sc);
	return (0);
}
