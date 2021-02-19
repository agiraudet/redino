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

# include <ncurses.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>

# define NONE 0
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
	int				win;
}					t_player;

typedef struct		s_object
{
	char			*chr;
	char			pch[2];
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
	char			*hint;
	char			*name;
}					t_level;

typedef struct	s_resolution
{
	int			wd;
	int			hg;
	int			off_x;
	int			off_y;
	int			map_wd;
	int			map_hg;
}				t_resolution;


/* MAIN */
int					win(void);

/* INIT */
void				init_ncurse(void);

/* PLAY */
int					play_all_lvl(const char *lvl_path);
int					play_solo_lvl(char *lvl_path);

/* UTILS */
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_nsplit(const char *str, const char *sep);

/* RENDER */
void				render_clean_screen(void);
void				render_level(t_level *lvl);
void				render_one_egg(t_egg *egg);
void				render_set_res(char **map);

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

/* UX */
void				ux_print_middle(int y, char *str, int color, int bold);
void				ux_print_title(void);
void				ux_title_screen(void);
void				ux_print_hint(char *str);
void				ux_print_name(char *str);
void				ux_init(void);

#endif
