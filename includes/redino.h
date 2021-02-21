/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redino.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:42:27 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/19 16:13:52 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDINO_H
# define REDINO_H

# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <SDL2/SDL.h>
# include "settings.h"

typedef struct		s_scene
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*atlas;
	int				wd;
	int				hg;
}					t_scene;

typedef struct		s_egg
{
	int				x;
	int				y;
	int				frame;
}					t_egg;

typedef struct		s_player
{
	int				frame;
	int				*sprite;
	int				*sprite_egg;
	int				x;
	int				y;
	int				color;
	int				egc;
	int				max_egg;
	t_egg			*egg;
	int				win;
}					t_player;

typedef struct		s_object
{
	int				frame;
	int				*sprite;
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
	int				map_size_x;
	int				map_size_y;
	t_player		*plr;
	char			*hint;
	char			*name;
}					t_level;

typedef struct		s_resolution
{
	int				wd;
	int				hg;
	int				off_x;
	int				off_y;
	int				map_wd;
	int				map_hg;
}					t_resolution;

/* PLAY */
int					play_all_level(t_scene *sc, const char *lvl_path);
int					play_one_level(t_scene *sc, char *lvl_path);
int					play_level(t_scene *sc, t_level *lvl);

/* UTILS */
void				hex_to_rgb(int hex, int *r, int *g, int *b);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_nsplit(const char *str, const char *sep);

/* RENDER */
void				render_level(t_scene *sc , t_level *lvl);
void				render_set_offset(t_scene *sc, t_level *lvl);

/* SCENE */
void				scene_destroy(t_scene *sc);
t_scene				*scene_create(char *title, int wd, int hg, const char *atlas_path);

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
int					player_is_near(t_obj *obj, t_player *plr);
int					player_move(t_level *lvl, SDL_Event event);

/* CONTROLLER */
void				ctl_destroy(t_ctl *ctl);
void				ctl_build_all(t_obj *objs);

/* OBJS */
void				obj_door_init_fct(t_ctl *ctl, int fct);
void				obj_lever_init_fct(t_ctl *ctl, int fct);
void				obj_portal_init_fct(t_ctl *ctl, int fct);
void				obj_spike_init_fct(t_ctl *ctl, int fct);
void				obj_check_init_fct(t_ctl *ctl, int fct);

/* LOADER */
t_level				*loader_lvl_create(void);
t_level				*loader_parse_file(char *file);
void				loader_parse_line(t_level *lvl, const char *line);

#endif
