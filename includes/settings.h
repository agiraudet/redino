/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 03:56:29 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/23 17:14:54 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define TITLE			"redino"
# define WIN_WD			800
# define WIN_HG			800
# define SCALE			3

# define DEBUG_FPS		0
# define MAX_FPS		60

# define PLAYER_SPEED	0.15
# define HITBOX			0.8

# define SPRITE_SIZE	16
# define ATLAS_SIZE		160
# define ATLAS_PATH		"assets/atlas.bmp"
# define LEVEL_PATH		"levels/"

# define FONT_PATH		"assets/TheConfession.ttf"
# define FONT_SIZE		20

# define GROUND_SPRITE	0
# define WALL_SPRITE	1

# define LEVER_SPRITE	"5,15"
# define DOOR_SPRITE	"3,13"
# define PLAYER_SPRITE	"2"
# define EGG_SPRITE		"4"
# define PORTAL_SPRITE	"6"
# define SPIKE_SPRITE	"7,17"
# define CHECK_SPRITE	"8"

# define PORTAL			1
# define SPIKE			2
# define LEVER			3
# define DOOR			4
# define CHECK			5

# define RED			0xFF0000
# define GREEN			0xFF00
# define BLUE			0xFF
# define WHITE			0xFFFFFF
# define BLACK			0x0

# define DEACT			0
# define ACT			1

# define MARGIN			40

# define COLOR_KEY		0xFF00FF

# define TXT_CENTER		0

# define KEY_UP			0
# define KEY_DOWN		1

# define NB_CD			3
# define ACT_ACT		0
# define ACT_EGG		1
# define ACT_HATCH		2
# define CD_ACT			200
# define CD_EGG			200
# define CD_HATCH		200 

#endif
