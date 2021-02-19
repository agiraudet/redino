/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redino.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:42:27 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 01:47:54 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDINO_H
# define REDINO_H

# include <ncurses.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

#define NONE 0
# define RED 1
# define GREEN 2
# define BLUE 3
# define WHITE 10
# define BLACK 11
# define BG_WHITE 100
# define BG_BLACK 101

# define DEACT 0
# define ACT 1

# define PORTAL 1
# define SPIKE 2
# define LEVER 3
# define DOOR 4
# define CHECK 5

typedef struct	s_egg
{
	int			x;
	int			y;
	int			color;
}				t_egg;

typedef struct		s_player
{
	int				x;
	int				y;
	int				color;
	int				egc;
	int				max_egg;
	t_egg			*egg;
	char			*chr;
}					t_player;

typedef struct		s_object
{
	char			*chr;
	int				status;
	int				type;
	int				x;
	int				y;
	int				color;
	struct s_ctl	*ctl;
	struct s_object	*next;
}					t_obj;

typedef struct		s_ctl
{
	t_obj			**parent;
	void			(*act)(t_obj*, t_player*);
	int				(*coll)(t_obj*, t_player*);
	int				(*logic)(int, int);
	void			(*update)(t_obj*);
	int				group;
	int				sensor;
}					t_ctl;

typedef struct		s_level
{
	t_obj			*objs;
	char			**map;
	t_player		*plr;
}					t_level;

/* MAIN */
int					win(void);

/* INIT */
void				init_ncurse(void);

/* UTILS */
char				**ft_nsplit(const char *str, const char *sep);

/* RENDER */
void				render_level(t_level *lvl);
void				render_one_egg(t_egg *egg);

/* LEVEL */
t_level				*level_load(char *lvl_file);
void				level_destroy(t_level *lvl);

/* EGGS */
int					egg_drop(t_player *plr);
void				egg_hatch(t_player *plr);

/* LOGIC */
int					logic_or(int parent_up, int parent_total);
int					logic_and(int parent_up, int parent_total);
int					logic_xor(int parent_up, int parent_total);
int					logic_xnor(int parent_up, int parent_total);
int					logic_nor(int parent_up, int parent_total);
int					logic_nand(int parent_up, int parent_total);

/* OBJECT */
void				object_destroy(t_obj *obj);
void				object_update(t_obj *obj);
void				object_act(t_obj *obj, t_player *plr);
void				object_add(t_obj **obj_lst, t_obj *obj);

/* PLAYER */
int					player_collision(char **map, t_obj *objs, t_player *plr, int y, int x);
int					player_move(char **map, t_obj *obj, t_player *plr);

/* CONTROLLER */
void				ctl_destroy(t_ctl *ctl);
void				ctl_build_all(t_obj *objs);

/* OBJS */
void				obj_door_init_fct(t_ctl *ctl, int fct);
void				obj_lever_init_fct(t_ctl *ctl, int fct);
void				obj_portal_init_fct(t_ctl *ctl, int fct);
void				obj_spike_init_fct(t_ctl *ctl, int fct);
void				obj_check_init_fct(t_ctl *ctl, int fct);

/* MSON */
t_level				*mson_parse_file(char *file);

#endif
