/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:37:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 21:59:11 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <sys/time.h>
# include <libft.h>
# include <raycast.h>
# include <thread.h>
# include <controllers.h>

#define HERE write(2, "here\n", 5)
#define ALMOST write(2, "almost\n", 8)
#define THERE write(2, "there\n", 6)
#define SCALE 50
#define X 0
#define Y 1

typedef struct s_engine	t_engine;
typedef struct s_object	t_object;
typedef struct s_map	t_map;
typedef void 			(*t_exe)(t_object*, t_object*);
typedef struct s_gui	t_gui;
typedef struct s_image	t_image;

//Don't move.
enum {
	EA, WE, SO, NO
};

enum {
	F, C
};

enum {
	ESC = 65307,
	SPACE = 32,
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	SHIFT = 65505,
	KEY_ARROW_UP = 65362,
	KEY_ARROW_RIGHT = 65363,
	KEY_ARROW_DOWN = 65364,
	KEY_ARROW_LEFT = 65361,
};

//Don't move DOOR from place.
typedef enum e_type {
	FLOOR,
	PLAYER,
	ENEMY,
	WALL,
	DOOR,
	DEMENTOR,
	MAGE,
	SPELL,
	P_SPELL = SPELL + PLAYER,
	E_SPELL = SPELL + ENEMY,
	D_SPELL = SPELL + DOOR,
	DEMENTOR_SPELL = SPELL + DEMENTOR,
	W_SPELL = SPELL + WALL,
	PATRONO,
	END_SPELL,
	MAGE_SPELL,
	O_DOOR,
	C_DOOR,
	NONE,
	GOOD,
	EVIL,
	HEAD
} t_type;

struct s_map {
	char		**map;
	char		**copy;
	int			height;
	int			width;
	int			pixelheight;
	int			pixelwidth;
	int			middle;
	int			player_posx;
	int			player_posy;
	int			size;
	void		*textures[5];
	int			colors[3];
	char		*colors_str[3];
};

struct s_image {
	int		id;
	void	*img;
	void	**album;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
};

struct	s_gui {
	void	*mlx;
	void	*win;
	int		key;
	t_image	canvas;
};

typedef struct	s_render
{
	t_image	*art;
	int		on_screen;
	double	max_size[2];
	double	screen[2];
	double	size[2];
	double	step[2];
	double	distance;
	double	height;
	double	width;
} t_render;

typedef struct	s_skill {
	int		cooldown;
	double	last;
	void	*(*new)();
	int		index;
} t_skill;

struct s_object {
	t_type		id;
	t_type		alliance;
	float		life;
	float		damage;
	int			vulnerable;
	float		space;
	double		x;
	double		y;
	double		vector[2];
	double		sidevector[2];
	t_line		cross;
	t_render	render;
	t_image		*spell;
	t_object	*on_top;
	t_skill		spellbook[4];
	t_skill		attack;
	t_skill		block;
	t_skill		active;
	t_skill		end;
	t_skill		animation;
	int			direction;
	void		(*move)(t_object *);
	void		(*update)(t_object *);
	void		(*collide)(t_object *, t_object *);
	void		(*destroy)(t_object *);
};

typedef struct s_array {
	t_object	*array;
	int			size;
	int			length;
	int			height;
	t_object	invalid;
} t_array;

typedef struct s_fullmatrix {
	t_object	*(*element)(int, int);
	void		(*forEach)(void (*)());
	t_matrix	*(*create)(char **);
	void		(*destroy)(void);
	t_array		this;
} t_fullmatrix;

struct s_engine {
	t_map		map;
	t_gui		game;
	t_collect	*on_screen;
	t_object	*player;
	int			game_on;
	double		time;
	void		(*minimap)(void);
	char		*paths[2];
};

struct s_player {
	t_type	id;
	double	x;
	double	y;
	double	vector[2];
	double	sidevector[2];
	t_image	*art;
	t_line	cross;
	void	(*destroy)(t_object *);
};

void				update_sprite(t_object *object);
t_object			*new_enemy(double x, double y);
void				init_images(void);
void				on_screen_add(t_object *object, t_collect *collect);
double				object_distance(t_object *first, t_object *second);
int					bigger_line(char **matrix);

t_object			*new_power(t_object *holder);
t_object			*new_patrono(t_object *holder);
t_object			*new_door(double x, double y);
t_object			*new_mage(double x, double y);
t_image				*new_album(char *path, t_type id);
t_object			*new_event(double x, double y);
void				update(t_engine *engine);

void				print_wall(t_ray *ray);
void				set_wall(t_render *wall, t_ray *ray);
t_image				*give_wall_sprite(t_ray *ray);
void				painting_ceiling_floor(t_ray *ray, double height, double middle);


void				set_ray(t_ray *ray, t_object *object, double *column);
void				select_point(t_ray *ray, t_object *object);
void				ray_rotate(t_ray *ray);
void				set_rotation(t_ray *ray, double angle);
void				raycast_split(t_object *object);
void				raycast(t_ray *ray, double *pos, int x, int y);


int					throw_skill(t_object *object, t_skill *skill);
t_matrix			*matrix(void);

t_image				*new_sprite(char *path, t_type id);


void				free_map_remove(t_object *object);
void				seek_and_destroy(t_object *object, t_object *target);
void				attack_target(t_object *object);

int					square_collision(t_object *object, double straight, double sideway);
void				surround_collision(t_object *object);
void				release_power(t_object *holder);

void				obj_stack_remove(t_object *list, t_object *remove);
void				obj_stack_add(t_object *list, t_object *add);

void				ft_bubble_sort(t_render **list, int size);
void				paint_sprite_column(t_ray *ray, t_render *object);
void				paint_objects_column(t_ray *ray, t_object *object);

void				**sprites(t_type find);
t_list				**onstage(void);
t_list				**offstage(void);
t_engine			*engine(void);
char				*on(int press);

void				do_nothing(void);
double				object_distance(t_object *first, t_object *second);

int					my_mlx_pixel_get(t_image *art, int x, int y);


void				remove_from_list(void *find, t_list **head);

void				object_update(t_object *object);
void				mouse_action(int key, t_engine *engine);


void				setdefaultobject(t_object *object, int position);
void				**this(void);
int					split_size(char **split);
char				**free_matrix(char **arr);
char				**clone_matrix(t_map *map);

char				*substr_name_file(char *str);
int					validate_name_file(char *name);
void				rotate_vector(double *origin, double angle);

void				*free_null(void **mem);

unsigned long		get_time(void);


//--Player
void				position_start_vector(t_object *player);
void				patrono_update(t_object *object);
t_object			*new_patrono(t_object *holder);
void				create_wall(t_object *object);
void				destroy_wall(t_object *object);
void				catch_spells(t_object *object, t_object *target);
void				player_move(t_object *object);
t_object			*new_player(double x, double y);
t_object			*new_wall_spell(t_object *holder);
t_object			*new_block_spell(t_object *holder);
void				patrono_block(t_object *object, t_object *target);
void				end_spell(t_object *block);
void				patrono_update(t_object *object);
t_object			*new_block_spell(t_object *holder);
t_object			*new_wall_spell(t_object *holder);

// int				filetomatrix(t_map *vmap, char *line, int fd, int pos);
void				get_info(char *name);

void				game_setup(t_engine *engine, int argc, char **argv);
char				**clone(t_map *tab);
void				flood_fill(char **map, int x, int y);
void				validate_map(t_map *map, char *name);
// void				create_objects(t_map *map);


int					key_down(int keycode, t_engine *engine);
int					key_up(int keycode, t_engine *engine);
char				*get_next_line(int fd);


void				end_game(char *message);
int					keypress(int keycode);

void				my_mlx_pixel_put(t_image *data, int x, int y, int color);

// Organizing
// ray
double				valid_position(double position, double limit);
// void				raycast(double *pos, double *vector, int *point);
void				print_wall(t_ray *ray);
void				spread_ray(t_object *object, double *interval);
// painting
void				my_mlx_pixel_put(t_image *data, int x, int y, int color);
void				paint_player();
void				painting_map(void);
// Movement
int					stoi(double position);
void				movement(t_object *object);
// Vector
// void				rotate_vector(double *change, double angle);
void				update_vector(t_object *object);

void				set_tasker(t_tasker *handler, int id);

// void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
// int					my_mlx_pixel_get(t_img *data, int x, int y);

//----Validate Map

int					empty_string(char *str);
void				print_map(t_map *map);
char				**filetomatrix(char **matrix, int counter, int fd);
char				*allocate_and_fill(int size, int value);
void				add_border(t_map *map);
void				get_file(t_map *map, char *name);
void				file_tomap(t_map *map);
void				larger_line(t_map *map);
void				get_dimensions(t_map *map);
int					not_space(char *name);
void				clean_my_array(t_map *map);
void				elements_counter(t_map *map, int counter);
void 				list_textures_elements(t_map *map, int counter);
void				print_elements(t_map *map);
void				clean_textures_broken(t_map *map, int counter);
void				check_open_textures(t_map *map);
void				check_characters(t_map *map);
void				flooding_map(t_map *map);
int					check_rgb(char **arr);
int					isnumber(char *s);
void				alpha_security(t_map *map);
int					limit_rgb(int red, int green, int blue);
void				check_colors(t_map *map, int red, int green, int blue);
void				textures_control(t_map *map);
void				check_array(t_map *map, int	*arr);




#endif
