#ifndef CUB3D_H
# define CUB3D_H

# include "lib_gnl/gnl/get_next_line.h"
# include "lib_gnl/lib/libft.h"
# include <fcntl.h>
# include <math.h>

//delete later
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
DATA:
	1- DIRECTION TEXTURES: IT HAS 2 ARGUMENTS *ID AND *DESTINATION
	2- FLOOR COLOR: IT HAS 4 ARGUMENTS *ID *RED *GREEN *BLUE
	3- CEILING COLOR: IT HAS 4 ARGUMENTS *ID *RED *GREEN *BLUE
	4- MAP
*/

# define GRID 64
# define PLAYER_HEIGHT 32
# define PLANE_HEIGHT 1024
# define PLANE_WIDTH 1024
# define PLAYER_DISTANCE (1024 / 2) / tan(30)
# define FOV 60
# define PLANE_CENTERX 1024 / 2
# define PLANE_CENTERY 1024 / 2
# define RAY_ANGLE 60 / 1024

typedef struct s_raycast
{
	float		radian;
	int			hx;
	int			hy;
	int			vx;
	int			vy;
	int			sin_ang;
	int			cos_ang;
	int			tan_ang;
	double		next_h;
	double		next_v;
	int			dist_h;
	int			dist_v;
}				t_rcst;

typedef struct s_texture
{
	char		id[3];
	char		dest[200];
}				t_texture;

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
	char		map[1024][1024];
	int			visited[1024][1024];
	int			height;
	int			px;
	int			py;
	int			player_height;
	int			player_fov;
	int			player_plane_distance;
	int			player_angle;
	int			plane_height;
	int			plane_width;
	int			plane_center_x;
	int			plane_center_y;
	int			ray_angle;
}				t_data;

int		parse_file(int fd, t_data *data);
void	find_player_location(t_data *data);
void	check_data(t_data *data);
int		ft_error(char *str);

#endif