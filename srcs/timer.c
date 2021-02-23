/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:22:21 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/23 16:23:55 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"

void		timer_init(t_timer *time)
{
	int		i;

	i = 0;
	while (i < NB_CD)
		time->cd[i++] = 0;
	time->start_time = SDL_GetTicks();
	time->relative_time = 0;
	time->frames = 0;
	time->avg_fps = 0;
	
}

void		timer_update(t_timer *time)
{
	time->relative_time = SDL_GetTicks() - time->start_time;
	time->frames += 1;
	if (time->frames > 200000)
		time->frames = 0;
	time->avg_fps = time->frames / (time->relative_time / 1000.);
}

int			timer_get_fps(t_timer *time)
{
	return ((int)time->avg_fps);
}

void		timer_cap_fps(t_timer *time)
{
	int		frame_ticks;

	frame_ticks = SDL_GetTicks() - time->start_time - time->relative_time;
	if (frame_ticks < 1000 / MAX_FPS)
		SDL_Delay(1000 / MAX_FPS - frame_ticks);
}

void		timer_init_cd(t_timer *time)
{
	int		i;

	i = 0;
	while (i < NB_CD)
		time->cd[i++] = time->relative_time;
}

int			timer_check_cd(t_timer *time, int action, int cd_duration)
{
	if (time->cd[action] + cd_duration <= time->relative_time)
		return (1);
	return (0);
}

void		timer_reset_cd(t_timer *time, int action)
{
	time->cd[action] = time->relative_time;
}
