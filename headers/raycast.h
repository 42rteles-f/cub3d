/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:01:35 by lliberal          #+#    #+#             */
/*   Updated: 2023/10/27 20:37:14 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <math.h>
# include <cub3d.h>

#define S_ANGLE 30

typedef struct s_ray	t_ray;
typedef struct s_object	t_object;
typedef struct s_hit	t_hit;
typedef struct s_collect t_collect;


typedef struct s_line {
	double	m;
	double	b;
} t_line;

struct s_hit {
	double		point[2];
	int			wall;
	t_object	*object;
};

struct s_ray {
	int			column;
	double		vector[2];
	double		hold[2];
	double		radians;
	double		cos;
	double		sin;
	double		distance;
	t_hit		hit[2];
	t_collect	*on_screen;
	void		(*rotate)();
	void		(*cast)();
	void		(*closest)();
	void		(*print)();
};

// struct s_ray {
// 	int		hit;
// 	double	posX;
// 	double	posY;
// 	double	dirX;
// 	double	dirY;
// 	double	planeX;
// 	double	planeY;
// 	double	time;
// 	double	oldtime;
// 	// -----------------
// 	double 	cameraX;
// 	double 	cameraY;
// 	double	rayDirX;
// 	double	rayDirY;
// 	//---------------
// 	int		mapX;
// 	int		mapY;
// 	double	sideDistX;
// 	double	sideDistY;
// 	double	deltaDistX;
// 	double	deltaDistY;
// 	double	stepX;
// 	double	stepY;
// 	int		side;
// 	double	perpWallDist;
// 	double	yDist;
// 	double	xDist;
// 	int		lineHeight;
// 	int		lineWidth;
// 	int		drawStart;
// 	int		drawEnd;
// };


// int				update(void	*engine);
void			ray_position_direction(t_ray *ray);
void			length_ray(t_ray *ray);
void			find_step_initial_sideDist(t_ray *ray);
void			ray_distanceToWall(t_ray *data);
void			calculate_height_line_on_screen(t_ray *data);
void			lowest_highest_pixel_in_stripe(t_ray *data);
void			dda_algorithym(t_ray *ray);

#endif