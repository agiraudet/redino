/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mson.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:52:30 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 02:14:14 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"
#include "get_next_line.h"

void	mson_destroy_token(char **token)
{
	int		i;
	
	i = 0;
	while (token[i])
		free(token[i++]);
	free(token);
}

void	mson_set_logic(t_ctl *ctl, const char *gate)
{
	if (strcmp(gate, "OR") == 0)
		ctl->logic = &logic_or;
	else if (strcmp(gate, "AND") == 0)
		ctl->logic = &logic_and;
	else if (strcmp(gate, "XOR") == 0)
		ctl->logic = &logic_xor;
	else if (strcmp(gate, "XNOR") == 0)
		ctl->logic = &logic_xnor;
	else if (strcmp(gate, "NOR") == 0)
		ctl->logic = &logic_nor;
	else if (strcmp(gate, "NAND") == 0)
		ctl->logic = &logic_nand;
	else
		ctl->logic = 0;
}

t_ctl	*mson_create_ctl(int type, int group, int mode, const char *gate)
{
	t_ctl	*ctl_tmp;

	if (type < 0)
		return (0);
	if (!(ctl_tmp = malloc(sizeof(t_ctl))))
		return (0);
	ctl_tmp->group = group;
	ctl_tmp->act = 0;
	ctl_tmp->coll = 0;
	ctl_tmp->update = 0;
	ctl_tmp->sensor = (mode & 8);
	mson_set_logic(ctl_tmp, gate);
	if (type == DOOR)
		obj_door_init_fct(ctl_tmp, mode);
	else if (type == LEVER)
		obj_lever_init_fct(ctl_tmp, mode);
	else if (type == PORTAL)
		obj_portal_init_fct(ctl_tmp, mode);
	else if (type == SPIKE)
		obj_spike_init_fct(ctl_tmp, mode);
	else if (type == CHECK)
		obj_check_init_fct(ctl_tmp, mode);
	else
	{
		free(ctl_tmp);
		return (0);
	}
	return (ctl_tmp);
}

int		mson_get_type(const char *str)
{
	if (strcmp(str, "door") == 0)
		return (DOOR);
	else if(strcmp(str, "lever") == 0)
		return (LEVER);
	else if (strcmp(str, "portal") == 0)
		return (PORTAL);
	else if (strcmp(str, "spike") == 0)
		return (SPIKE);
	else if (strcmp(str, "check") == 0)
		return (CHECK);
	else
		return (-1);
}

int		mson_get_color(const char *str)
{
	if (strcmp(str, "red") == 0)
		return (RED);
	else if (strcmp(str, "green") == 0)
		return (GREEN);
	else if (strcmp(str, "blue") == 0)
		return (BLUE);
	else if (strcmp(str, "white") == 0)
		return (WHITE);
	else if (strcmp(str, "black") == 0)
		return (BLACK);
	else if (strcmp(str, "bg_white") == 0)
		return (BG_WHITE);
	else if (strcmp(str, "bg_black") == 0)
		return (BG_BLACK);
	else
		return (0);
}

t_player	*mson_add_plr(const char *line)
{
	char	**token;
	t_player	*plr;

	if (!(token = ft_nsplit(line, " ,\t")))
		return (0);
	if (!(plr = malloc(sizeof(t_player))))
	{
		mson_destroy_token(token);
		return (0);
	}
	plr->max_egg = atoi(token[6]);
	if (!(plr->egg = malloc(sizeof(t_egg) * plr->max_egg)))
	{
		free(plr);
		mson_destroy_token(token);
		return (0);
	}
	plr->egc = 0;
	plr->chr = strdup(token[2]);
	plr->x = atoi(token[3]);
	plr->y = atoi(token[4]);
	plr->color = mson_get_color(token[5]);
	mson_destroy_token(token);
	return (plr);
}

void	mson_add_obj(t_obj **objs, const char *line)
{
	char	**token;
	t_obj	*obj_tmp;
	t_ctl	*ctl_tmp;
	
	if (!(token = ft_nsplit(line, " ,\t")))
		return ;
	if (!(obj_tmp = malloc(sizeof(t_obj))))
	{
		mson_destroy_token(token);
		return;
	}
	if (!(ctl_tmp = mson_create_ctl(mson_get_type(token[1]), atoi(token[7]), atoi(token[8]), token[9])))
	{
		free(obj_tmp);
		mson_destroy_token(token);
		return;
	}
	obj_tmp->chr = strdup(token[2]);
	obj_tmp->pch[0] = obj_tmp->chr[0];
	obj_tmp->pch[1] = 0;
	obj_tmp->x = atoi(token[3]);
	obj_tmp->y = atoi(token[4]);
	obj_tmp->color = mson_get_color(token[5]);
	obj_tmp->status = atoi(token[6]);
	obj_tmp->ctl = ctl_tmp;
	obj_tmp->next = 0;
	object_add(objs, obj_tmp);
	mson_destroy_token(token);
}

void	mson_add_map(char **map, const char *line)
{
	static int	i = 0;

	map[i++] = strdup(line);
}

void	mson_parse_line(t_level *lvl, const char *line)
{
	if (*line == 'O')
		mson_add_obj(&lvl->objs, line);
	else if (*line == 'w' || *line == ' ')
		mson_add_map(lvl->map, line);
	else if (*line == 'P')
		lvl->plr = mson_add_plr(line);
}

t_level	*mson_lvl_create(void)
{
	t_level	*lvl;

	if (!(lvl = malloc(sizeof(t_level))))
		return (0);
	lvl->objs = 0;
	lvl->map = calloc(500, sizeof(char*));
	lvl->plr = 0;
	return (lvl);
}

t_level	*mson_parse_file(char *file)
{
	int		fd;
	char	*line;
	t_level	*lvl;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	if (!(lvl = mson_lvl_create()))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '#')
			mson_parse_line(lvl, line);
		free(line);
	}
	free(line);
	ctl_build_all(lvl->objs);
	return (lvl);
}
