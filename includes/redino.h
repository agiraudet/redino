/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redino.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:42:27 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/23 16:21:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDINO_H
# define REDINO_H

# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include "settings.h"

typedef struct		s_timer
{
	uint32_t		start_time;
	int				relative_time;
	int				frames;
	double			avg_fps;
	int				cd[NB_CD];
}					t_timer;

typedef struct		s_scene
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*atlas;
	t_timer			time;
	int				wd;
	int				hg;
}					t_scene;

typedef struct		s_egg
{
	double			x;
	double			y;
	int				frame;
}					t_egg;

typedef struct		s_player
{
	int				frame;
	int				*sprite;
	int				*sprite_egg;
	double			x;
	double			y;
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
	char			*type;
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

typedef struct		s_txt
{
	SDL_Texture		*tex;
	SDL_Rect		dest;
	int				pos;
	char			*name;
	struct s_txt	*next;
}					t_txt;

typedef struct		s_text_manager
{
	TTF_Font		*font;
	struct s_txt	*txt;
}					t_text_manager;

typedef struct		s_input
{
	int				up;
	int				up_key;
	int				down;
	int				down_key;
	int				left;
	int				left_key;
	int				right;
	int				right_key;
	int				egg;
	int				egg_key;
	int				hatch;
	int				hatch_key;
	int				reset;
	int				reset_key;
	int				act;
	int				act_key;
	int				quit;
	int				quit_key;
}					t_input;


typedef struct		s_level
{
	t_obj			*objs;
	char			**map;
	int				map_size_x;
	int				map_size_y;
	t_player		*plr;
	t_text_manager	*tm;
	t_input			*inp;
	char			*hint;
	char			*name;
}					t_level;

/* PLAY */
int					play_all_level(t_scene *sc, const char *lvl_path);
int					play_one_level(t_scene *sc, char *lvl_path);
int					play_level(t_scene *sc, t_level *lvl);
void				level_init(t_scene *sc, t_level *lvl);

/* UTILS */
char				*ft_u32toa(uint32_t n);
void				hex_to_sdl_color(int hex, SDL_Color *color);
void				hex_to_rgb(int hex, int *r, int *g, int *b);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_nsplit(const char *str, const char *sep);

/* RENDER */
void				render_level(t_scene *sc , t_level *lvl);
void				render_set_offset(t_scene *sc, t_level *lvl);
void				render_text_init_pos_y(t_scene *sc, t_level *lvl);

/* SCENE */
void				scene_destroy(t_scene *sc);
t_scene				*scene_create(char *title, int wd, int hg, const char *atlas_path);

/* LEVEL */
t_level				*level_load(char *lvl_file);
void				level_destroy(t_level *lvl);
void				level_init_text(t_scene *sc, t_level *lvl);

/* EGGS */
int					egg_drop(t_level *lvl);
void				egg_hatch(t_player *plr);
int					player_behind_obj(t_player *plr, t_obj *obj);

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
int					player_is_near(double plr_x, double plr_y, int x, int y);
int					player_move(t_level *lvl, t_timer *time);

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

/* TEXT */
void				text_txt_destroy(t_txt *txt);
t_txt				*text_txt_create(t_scene *sc, t_text_manager *tm, const char *str, int hex);
void				text_manager_destroy(t_text_manager *tm);
void				text_txt_add(t_scene *sc, t_text_manager *tm, const char *str, int hex);
void				text_txt_add_multiple(t_scene *sc, t_text_manager *tm, char **strs, int hex);
t_text_manager		*text_manager_create(const char *font_path, int font_size);
void				text_manager_init_pos_x(t_scene *sc, t_text_manager *tm);

/* INPUT */
void				input_destroy(t_input *inp);
t_input				*input_create(void);
void				input(t_input *inp, SDL_Keycode key, int state);

/* TIME */
void				timer_init(t_timer *time);
void				timer_update(t_timer *time);
int					timer_get_fps(t_timer *time);
void				timer_cap_fps(t_timer *time);
void				timer_init_cd(t_timer *time);
int					timer_check_cd(t_timer *time, int action, int cd_duration);
void				timer_reset_cd(t_timer *time, int action);

#endif
