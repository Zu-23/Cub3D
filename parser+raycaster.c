#include "lib_gnl/gnl/get_next_line.h"
#include "lib_gnl/lib/libft.h"
#include <fcntl.h>
#include <math.h>
#include "mlx_repo/MLX42/MLX42.h"

//delete later
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

/*
DATA:
	1- DIRECTION TEXTURES: IT HAS 2 ARGUMENTS *ID AND *DESTINATION
	2- FLOOR COLOR: IT HAS 4 ARGUMENTS *ID *RED *GREEN *BLUE
	3- CEILING COLOR: IT HAS 4 ARGUMENTS *ID *RED *GREEN *BLUE
	4- MAP
*/

#define	GRID			64
#define PLAYER_HEIGHT	32
#define PLANE_HEIGHT	1024
#define PLANE_WIDTH		1024
#define PLAYER_DISTANCE	886.81	//(1024 / 2) / tan(30)
#define	FOV				60
#define PLANE_CENTER	1024 / 2
#define	RAY_ANGLE		0.058	//60 / 1024
#define	GRID_DIV_PROJ	64 * 1024 //GRID * PLAYER_DISTANCE

typedef struct s_wall
{
	int	hit;
	int	side_hit;
	int	imgcol;
	int	wall_x;
	int	wall_y;
	int	wall_dist;
}t_wall;
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
}t_rcst;

typedef struct s_texture
{
	char	id[3];
	char	dest[200];
}t_texture;

typedef struct s_var
{
	int	i;
	int	j;
	int	k;
}t_var;

typedef struct s_color
{
	char	id[2];
	int		red;
	int		green;
	int		blue;
}t_color;

typedef struct s_data
{
	t_texture	no;
	t_texture	so;
	t_texture	ea;
	t_texture	we;
	t_color		f;
	t_color		c;
	char		map[1024][1024];
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
	mlx_t		*mlx;
	mlx_image_t	*img;
}t_data;

int	ft_error(char *str)
{
	perror(str);
	exit(1);
}

int	ft_isspace(int c)
{
	return ((c == '\f') || (c == '\r') || (c == '\t') || (c == '\v'));
}

int	fill_texture(char *line, t_texture *texture, int *success)
{
	char	*after_xpm;

	after_xpm = ft_strstr(line, ".xpm") + 4;
	while (after_xpm != (char *)4 && *after_xpm != '\n')
	{
		if (*after_xpm != ' ')
			return (-1);
		after_xpm++;
	}
	if (texture->id[0] != '\0')
		return (-1);
	ft_strcpy(texture->id, ft_strtok(line, " "));
	ft_strcpy(texture->dest, ft_strtok(NULL, " \n"));
	printf("id: %s\ndest: %s\n", texture->id, texture->dest);
	if (ft_strstr(texture->dest, ".xpm") == NULL) //need to look at this later.
		return (-1);
	*success = 1;
	return (0);
}

int	check_rgb(char *rgb)
{
	int	i;

	i = 0;
	//printf("RGB: %s\n", rgb);
	if (rgb == NULL)
		return (-1);
	while (rgb[i])
	{
		if (ft_isdigit(rgb[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	fill_color(char *line, t_color *color, int *success)
{
	char	*rgb[3];
	int		i;

	i = 0;
	if (color->id[0] != '\0')
		return (-1);
	ft_strcpy(color->id, ft_strtok(line, " "));
	while (i < 3)
	{
		rgb[i] = ft_strtok(NULL, " ,\n");
		if (check_rgb(rgb[i++]))
			return (-1);
	}
	color->red = ft_atoi(rgb[0]);
	color->green = ft_atoi(rgb[1]);
	color->blue = ft_atoi(rgb[2]);
	if ((color->red < 0 || color->red > 255)
		|| (color->green < 0 || color->green > 255)
		|| (color->blue < 0 || color->blue > 255))
		return (-1);
	*success = 1;
	printf("id %s red %d green %d blue %d\n", color->id,color->red, color->green, color->blue);
	return (0);
}

int	parse_color(char *line, t_data *data, int *success)
{
	if (line[0] == 'C' && line[1] == ' ')
	{
		if (fill_color(line, &data->c, success))
			return (-1);
	}
	else if (line[0] == 'F' && line[1] == ' ')
	{
		if (fill_color(line, &data->f, success))
			return (-1);
	}
	return (0);
}

int	parse_texture(char *line, t_data *data, int *success)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		if (fill_texture(line, &data->no, success))
			return (-1);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		if (fill_texture(line, &data->so, success))
			return (-1);
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if (fill_texture(line, &data->ea, success))
			return (-1);
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		if (fill_texture(line, &data->we, success))
			return (-1);
	}
	return (0);
}

int check_valid_line(char *line, t_data *data)
{
    char *content;
    int i;
	int	j;	

    i = 0;
	j = 0;
	content = "01NSWE";
	if (!data->ea.id[0] || !data->no.id[0]
		|| !data->so.id[0] || !data->we.id[0]
		|| !data->c.id[0] || !data->f.id[0])
			return (-1);
    while (line[j] && line[j] != '\n')
    {
        while (line[j] == ' ')
            j++;
        while (content[i] && content[i++] != line[j]);
        if (content[i] == '\0')
            return (-1);
        i = 0;
        j++;
    }
    return (0);
}

int	parse_map(char *line, t_data *data)
{
	char	*str;
	t_var   var;

	var.i = 0;
    var.j = 0;
    var.k = 0;
    if (check_valid_line(line, data))
        return (-1);
    str = malloc(ft_strlen(line) + 1);
    if (!str)
        return (-1);
	while (line[var.i] && line[var.i] != '\n')
	{
		while (line[var.i] == ' ')
            var.i++;
		str[var.j++] = line[var.i++];
	}
    str[var.j] = '\0';
	ft_strcpy(data->map[data->height++], str);
	// printf("map: %s\n", data->map[data->height-1]);
	free(str);
	return (0);
}



int	evaluate_parse_functions(char *line, t_data *data)
{
	int	success;

	success = 0;
	if (line[0] == '\n')
		return (0);
	if (parse_texture(line, data, &success))
		return (-1);
	if (success == 1)
		return (0);
	if (parse_color(line, data, &success))
		return (-1);
	if (success == 1)
		return (0);
	if(parse_map(line, data))
		return (-1);
	return (0);
}

int	parse_file(int fd, t_data *data)
{
	int		error;
	char	*line;

	error = 0;
	line  = get_next_line(fd);
	if (line == NULL)
		ft_error("Error\nin file handling\n");
	while (line)
	{
		if (evaluate_parse_functions(line, data))
		{
			error = -2;
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (error)
		ft_error("Error\nin file parsing\n");
	return (0);
}

int	check_player_position(t_data *data)
{
	t_var	var;
	int		p_pos;

	var.i = 0;
	var.j = 0;
	p_pos = 0;
	while (var.j < data->height)
	{
		while (data->map[var.j][var.i])
		{
			if (data->map[var.j][var.i] != '0'
			&& data->map[var.j][var.i] != '1')
			{
				if (p_pos == 0)
					p_pos = 1;
				else
					return (-1);
			}
			var.i++;
		}
		var.j++;
		var.i = 0;
	}
	return (0);
}

int	check_closed_walls(t_data *data)
{
	t_var	var;

	var.i = 0;
	var.j = 0;
	while (data->map[0][var.i])
	{
		if (data->map[0][var.i++] != '1')
			return (-1);
	}
	var.i = 0;
	while (data->map[data->height - 1][var.i])
	{
		if (data->map[data->height - 1][var.i++] != '1')
			return (-1);
	}
	while (var.j < data->height)
	{
		if (data->map[var.j][0] != '1'
		|| data->map[var.j][ft_strlen(data->map[var.j]) - 1] != '1')
			return (-1);
		var.j++;
	}
	return (0);
}

int	check_map(t_data *data)
{
	if (check_player_position(data) || check_closed_walls(data))
		return (-1);
	return (0);
}

void	check_data(t_data *data)
{
	if (!data->ea.id[0] || !data->no.id[0]
		|| !data->so.id[0] || !data->we.id[0])
		ft_error("Error\nincorrect walls texture inputs\n");
	if (!data->c.id[0] || !data->f.id[0])
		ft_error("Error\nincorrect floor or ceiling inputs\n");
	if (check_map(data))
		ft_error("Error\nincorrect map inputs\n");
}




















////////////////////////////////	WHATEVER THAT IS ABOVE IS PARSING!!! ///////////////////////////////////////////////
// //// // // // / ///// /////// //// // // // / ///// /////// //// // // // / ///// /////// //// // // // / ///// /////
// //// // // // / ///// /////// //// // // // / ///// /////// //// // // // / ///// /////// //// // // // / ///// /////
// //// // // // / ///// /////// //// // // // / ///// /////// //// // // // / ///// /////
// //// // // // / ///// ///// RAYCASTER STARTS HERE! RAYCASTER STARTS HERE // //// // // // / ///// /////




void	check_player_angle(char p, t_data *data)
{
	if (p == 'E')
		data->player_angle = 0;
	else if (p == 'N')
		data->player_angle = 90;
	else if (p == 'W')
		data->player_angle = 180;
	else if (p == 'S')
		data->player_angle = 270;
	return ;
}

void	find_player_location(t_data *data)
{
	t_var var;

	var.j = 0;
	while (var.j < data->height)
	{
		var.i = 0;
		while (data->map[var.j][var.i])
		{
			if (ft_strchr("NSWE", data->map[var.j][var.i]))
			{
				data->px = var.i * GRID - 32;
				data->py = var.j * GRID - 32;
				check_player_angle(*(ft_strchr("NSWE", data->map[var.j][var.i])), data);
				return;
			}
			var.i++;
		}
		var.j++;
	}
}



int	find_intersection(double iter_ray, int column, t_data *data, t_rcst *ray)
{
	ray->radian = iter_ray * (3.14 / 180.0) - atan((PLANE_WIDTH / 2 - column) / PLAYER_DISTANCE);
	ray->cos_ang = cos(ray->radian);
	ray->sin_ang = sin(ray->radian);
	ray->tan_ang = ray->sin_ang / ray->cos_ang;
	if (-ray->sin_ang < 0)
		ray->hy = floor(data->py / GRID) * GRID - 1;
	else
		ray->hy = floor(data->py / GRID) * GRID + GRID;
	ray->hx = data->px + (data->py - ray->hy) / ray->tan_ang;
	if (ray->cos_ang < 0)
		ray->vx = floor(data->px / GRID) * GRID - 1;
	else
		ray->vx = floor(data->px / GRID) * GRID + GRID;
	ray->vy = data->py + (data->px - ray->vx) * ray->tan_ang;
	ray->next_h = fabs(GRID / ray->sin_ang); //check permadi for a different approach
	ray->next_v = fabs(GRID / ray->cos_ang);
	ray->dist_h = sqrt((data->px - ray->hx) * (data->px - ray->hx) + //distance to the first intersect
	(data->py - ray->hy) * (data->py - ray->hy));
	ray->dist_v = sqrt((data->px - ray->vx) * (data->px - ray->vx) +
	(data->py - ray->vy) * (data->py - ray->vy));

	return (0);
}

int	check_wall_collision(t_data *data, t_rcst *ray, t_wall *wall)
{
	wall->hit = 0;
	while (wall->hit == 0)
	{
		if (ray->dist_h <= ray->dist_v)
		{
			if (data->map[(int)ray->hy / GRID][(int)ray->hx / GRID] == '1')
			{
				wall->hit = 1;
				wall->wall_dist = ray->dist_h;
				wall->wall_x = ray->hx;
				wall->wall_y = ray->hy;
			}
			else
			{
				ray->dist_h += ray->next_h;
				ray->hx += ray->next_h * ray->cos_ang;
				ray->hy += ray->next_h * -ray->sin_ang;
			}
		}
		else
		{
			if (data->map[(int)ray->vy / GRID][(int)ray->vx / GRID] == '1')
			{
				wall->hit = 1;
				wall->wall_dist = ray->dist_v;
				wall->wall_x = ray->vx;
				wall->wall_y = ray->vx;
			}
			else
			{
				ray->dist_v += ray->next_v;
				ray->vx += ray->next_v * ray->cos_ang;
				ray->vx += ray->next_v * -ray->sin_ang;
			}
		}
	}
	return (0);
	// check_wall_horizontal
	// chec_wall_vertical
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_wall(int col, t_rcst *ray, t_data *data, t_wall *wall)
{
	double	wall_height;
	double	top_wall;
	double	i;

	i = 0;
	(void) ray;
	(void) col;
	(void) data;
	//double wall_height1 = ceil(GRID_DIV_PROJ / wall->wall_dist); // could be used in the same equation for top wall
	wall_height = ceil(GRID / wall->wall_dist * PLAYER_DISTANCE);
	top_wall = PLANE_CENTER - (wall_height / 2);
	while (i < wall_height)
	{
		uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
		mlx_put_pixel(data->img, col , top_wall + i, color);
		i++;
	}
}

int	raycasting(t_data *data)
{
	double	iter_ray;
	int		col;
	t_rcst 	ray;
	t_wall	wall;

	iter_ray = data->player_angle - (FOV / 2);
	col = 0;
	while (col < PLANE_WIDTH)
	{
		find_intersection(iter_ray, col, data, &ray);//we will try to put a while in CWC
		check_wall_collision(data, &ray, &wall);
		draw_wall(col, &ray, data, &wall);
		col++;
		iter_ray += RAY_ANGLE;
	}
	return (0);
}

void	mlxinit(t_data *data)
{
	data->mlx = mlx_init(PLANE_WIDTH, PLANE_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		ft_error("mlx failed\n");
	data->img = mlx_new_image(data->mlx, PLANE_WIDTH, PLANE_HEIGHT);
	if (!data->img)
		ft_error("img failed\n");
}

// void	buttons_hook(void *param)
// {
// 	mlx_t	*mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		//action
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		//action
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		//action
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		//actin
// }

int main(int ac, char **av)
{
	t_data		data;
	int			fd;

	ft_memset(&data, 0, sizeof(t_data));
	mlxinit(&data);
	if (ac == 2)
	{
		////PARSING TEST//////////
		fd = open(av[1], O_RDONLY);
		parse_file(fd, &data);
		check_data(&data);
		//////END OF PARSING TEST/////
		find_player_location(&data);
		raycasting(&data);
		//mlx_loop_hook(data.mlx, buttons_hook, data.mlx);
		mlx_loop(data.mlx);
		mlx_terminate(data.mlx);
	}
	else
		ft_error("Error\nwrong number of arguments\n");
}