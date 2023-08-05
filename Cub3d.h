/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:36:10 by alemsafi          #+#    #+#             */
/*   Updated: 2023/08/06 00:27:24 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "lib_gnl/lib/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define D 2
# define S 1
# define A 0
# define W 13
# define LEFT 123
# define RIGHT 124
# define ESC 53
# define GRID 64
# define MAP_GRID 8
# define PLANE_HEIGHT 1024
# define PLANE_WIDTH 1024
# define PLAYER_DISTANCE 886.81
# define FOV 60
# define PLANE_CENTER 512
# define RAY_ANGLE 0.058

typedef struct s_raycast
{
	float		radian;
	double		hx;
	double		hy;
	double		vx;
	double		vy;
	double		sin_ang;
	double		cos_ang;
	double		tan_ang;
	double		next_h;
	double		next_v;
	double		dist_h;
	double		dist_v;
}				t_rcst;

typedef struct s_texture
{
	char		id[3];
	char		dest[200];
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_wall
{
	int			hit;
	int			side_hit;
	int			imgcol;
	double		wall_x;
	double		wall_y;
	double		wall_dist;
}				t_wall;

typedef struct s_var
{
	int			i;
	int			j;
	int			k;
}				t_var;

typedef struct s_color
{
	char		id[2];
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct s_data
{
	t_texture	no;
	t_texture	so;
	t_texture	ea;
	t_texture	we;
	t_color		f;
	t_color		c;
	char		map[PLANE_WIDTH][PLANE_HEIGHT];
	int			visited[PLANE_WIDTH][PLANE_HEIGHT];
	int			height;
	double		px;
	double		py;
	double		player_x;
	double		player_y;
	int			player_fov;
	int			player_angle;
	int			plane_height;
	int			plane_width;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			up;
	int			down;
	int			left;
	int			right;
	int			turn_left;
	int			turn_right;
}				t_data;
/****************PARSING FUNCTIONS*******************/

void			check_data(t_data *data);
int				check_map(t_data *data);
int				parse_file(int fd, t_data *data);
int				parse_map(char *line, t_data *data, int flag);
int				evaluate_parse_functions(char *line, t_data *data);
int				check_player_position(t_data *data);
int				backtrack(t_data *data, int row, int col);
int				ft_error(char *str);
int				check_rgb(char *rgb);
int				parse_color(char *line, t_data *data, int *success);
int				fill_texture(char *line, t_texture *texture, int *success);
int				fill_color(char *line, t_color *color, int *success);
int				parse_texture(char *line, t_data *data, int *success);
int				check_valid_line(char *line, t_data *data);
int				check_closed_walls(t_data *data);
int				ft_isspace(char c);

/***********************************/
void			find_player_location(t_data *data);
void			render(t_data *data);
int				raycasting(t_data *data);
void			my_mlx_put_pixel(t_data *data, int x, int y, int color);
void			draw_sky_floor(t_data *data);
void			draw_map(t_data *data);
void			draw_player(t_data *data);
void			draw_wall(int col, t_rcst *ray, t_data *data, t_wall *wall);
unsigned int	get_color(t_texture *texture, int x, int y);
void			move_backwards(t_data *data, int x, int y);
void			move_forward(t_data *data, int x, int y);
void			move_left(t_data *data, int x, int y);
void			move_right(t_data *data, int x, int y);
void			turn_left(t_data *data);
void			turn_right(t_data *data);
int				key_hook(int keycode, t_data *data);
int				exit_hook(t_data *data);
int				key_release(int keycode, t_data *data);
int				loop_hook(t_data *data);
void			update(t_data *data);
void			get_textures(t_data *data);
int				check_wall_collision(t_data *data, t_rcst *ray, t_wall *wall,
					int col);
int				find_intersection(double iter_ray, int column, t_data *data,
					t_rcst *ray);

#endif