/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 04:45:52 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/20 05:13:04 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redino.h"
#include "get_next_line.h"

void	loader_destroy_token(char **token)
{
	int		i;
	
	i = 0;
	while (token[i])
		free(token[i++]);
	free(token);
}

void	loader_set_logic(t_ctl *ctl, const char *gate)
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

t_ctl	*loader_create_ctl(int type, int group, int mode, const char *gate)
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
	ctl_tmp->parent = 0;
	loader_set_logic(ctl_tmp, gate);
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
	return (ctl_tmp);
}

int		loader_get_type(const char *str)
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

int		loader_get_color(const char *str)
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
	else
		return (0);
}

int			*loader_add_sprite(char *sprite_str)
{
	char	**list_sprite;
	int		*arr;
	int		i;

	if (!(list_sprite = ft_nsplit(sprite_str, ",")))
		return (0);
	i = 0;
	while (list_sprite[i])
		i++;
	if (!(arr = malloc(sizeof(int) * (i + 1))))
	{
		loader_destroy_token(list_sprite);
		return (0);
	}
	i = 0;
	while (list_sprite[i])
	{
		arr[i] = atoi(list_sprite[i]);
		i++;
	}
	loader_destroy_token(list_sprite);
	return (arr);
}

char		*loader_get_sprite(char *type)
{
	if (strcmp(type, "door") == 0)
		return (DOOR_SPRITE);
	else if(strcmp(type, "lever") == 0)
		return (LEVER_SPRITE);
	else if (strcmp(type, "portal") == 0)
		return (PORTAL_SPRITE);
	else if (strcmp(type, "spike") == 0)
		return (SPIKE_SPRITE);
	else if (strcmp(type, "check") == 0)
		return (CHECK_SPRITE);
	else
		return (0);
}


t_player	*loader_add_plr(const char *line)
{
	char	**token;
	t_player	*plr;

	if (!(token = ft_nsplit(line, " \t")))
		return (0);
	if (!(plr = malloc(sizeof(t_player))))
	{
		loader_destroy_token(token);
		return (0);
	}
	plr->max_egg = atoi(token[5]);
	if (!(plr->egg = malloc(sizeof(t_egg) * plr->max_egg)))
	{
		free(plr);
		loader_destroy_token(token);
		return (0);
	}
	plr->win = 0;
	plr->egc = 0;
	plr->x = atoi(token[2]);
	plr->y = atoi(token[3]);
	plr->color = loader_get_color(token[4]);
	plr->sprite = loader_add_sprite(PLAYER_SPRITE);
	plr->sprite_egg = loader_add_sprite(EGG_SPRITE);
	plr->frame = 0;
	loader_destroy_token(token);
	return (plr);
}

void	loader_add_obj(t_obj **objs, const char *line)
{
	char	**token;
	t_obj	*obj_tmp;
	t_ctl	*ctl_tmp;
	
	if (!(token = ft_nsplit(line, " \t")))
		return ;
	if (!(obj_tmp = malloc(sizeof(t_obj))))
	{
		loader_destroy_token(token);
		return;
	}
	if (!(ctl_tmp = loader_create_ctl(loader_get_type(token[1]), atoi(token[6]), atoi(token[7]), token[8])))
	{
		free(obj_tmp);
		loader_destroy_token(token);
		return;
	}
	obj_tmp->x = atoi(token[2]);
	obj_tmp->y = atoi(token[3]);
	obj_tmp->color = loader_get_color(token[4]);
	obj_tmp->status = atoi(token[5]);
	obj_tmp->sprite = loader_add_sprite(loader_get_sprite(token[1]));
	obj_tmp->frame = 0;
	obj_tmp->ctl = ctl_tmp;
	obj_tmp->next = 0;
	object_add(objs, obj_tmp);
	loader_destroy_token(token);
}

void	loader_add_map(char **map, const char *line)
{
	int		i;

	i = 0;
	while (map[i])
		i++;
	map[i] = strdup(line);
}

char	*loader_add_text(const char *line)
{
	char	**token;
	char	*hint;

	token = ft_nsplit(line, "\"\t");
	hint = strdup(token[1]);
	loader_destroy_token(token);
	return (hint);
}

void	loader_parse_line(t_level *lvl, const char *line)
{
	if (*line == 'O')
		loader_add_obj(&lvl->objs, line);
	else if (*line == 'w' || *line == ' ')
		loader_add_map(lvl->map, line);
	else if (*line == 'P')
		lvl->plr = loader_add_plr(line);
	else if (*line == 'H')
		lvl->hint = loader_add_text(line);
	else if (*line == 'T')
		lvl->name = loader_add_text(line);
}

t_level	*loader_lvl_create(void)
{
	t_level	*lvl;

	if (!(lvl = malloc(sizeof(t_level))))
		return (0);
	lvl->objs = 0;
	lvl->map = calloc(500, sizeof(char*));
	lvl->plr = 0;
	lvl->hint = 0;
	lvl->name = 0;
	return (lvl);
}

t_level	*loader_parse_file(char *file)
{
	int		fd;
	char	*line;
	t_level	*lvl;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	if (!(lvl = loader_lvl_create()))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '#')
			loader_parse_line(lvl, line);
		free(line);
	}
	free(line);
	ctl_build_all(lvl->objs);
	return (lvl);
}
