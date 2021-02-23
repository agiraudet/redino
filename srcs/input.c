/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:11:51 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/22 16:41:59 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void		input_destroy(t_input *inp)
{
	free(inp);
	inp = 0;
}

t_input		*input_create(void)
{
	t_input		*inp;

	inp = malloc(sizeof(t_input));
	if (!inp)
		return (0);
	inp->up_key = SDLK_w;
	inp->down_key = SDLK_s;
	inp->left_key = SDLK_a;
	inp->right_key = SDLK_d;
	inp->egg_key = SDLK_e;
	inp->hatch_key = SDLK_r;
	inp->reset_key = SDLK_z;
	inp->act_key = SDLK_q;
	inp->quit_key = SDLK_ESCAPE;
	inp->up = 0;
	inp->down = 0;
	inp->left = 0;
	inp->right = 0;
	inp->egg = 0;
	inp->hatch = 0;
	inp->reset = 0;
	inp->act = 0;
	inp->quit = 0;
	return (inp);
}	

void		input(t_input *inp, SDL_Keycode key, int state)
{
	if (key == inp->up_key)
		inp->up = state;
	else if (key == inp->down_key)
		inp->down = state;
	else if (key == inp->left_key)
		inp->left = state;
	else if (key == inp->right_key)
		inp->right = state;
	else if (key == inp->egg_key)
		inp->egg = state;
	else if (key == inp->hatch_key)
		inp->hatch = state;
	else if (key == inp->reset_key)
		inp->reset = state;
	else if (key == inp->act_key)
		inp->act = state;
	else if (key == inp->quit_key)
		inp->quit = state;
}
