#include "42-functions/LIBFT_42/libft.h"
#include "42-functions/Get_next_line_42/get_next_line.h"
#include <fcntl.h>
#include <math.h>

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
#define PLAYER_DISTANCE	(1024 / 2) / tan(30)
#define	FOV				60
#define PLANE_CENTERX	1024 / 2
#define	PLANE_CENTERY	1024 / 2
#define	RAY_ANGLE		60/1024

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
	if (texture->dest == NULL || ft_strstr(texture->dest, ".xpm") == NULL)
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

int	parse_map(char *line, t_data *data, char *content)
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
	int len = ft_strlen(line);
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
	if(parse_map(line, data, "01NSWE"))
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

int	data_init(t_data *data)//might not be needed since we defined macros 
{
	ft_memset(data, 0, sizeof(t_data));
	data->plane_height = 1024;
	data->plane_width = 1024;
}


int	find_intersection(int iter_ray, int column, t_data *data)
{
	t_rcst ray;

	ray.radian = iter_ray * 3.14 / 180.0 - atan((PLANE_WIDTH / 2 - column) / PLAYER_DISTANCE);
	ray.cos_ang = cos(ray.radian);
	ray.sin_ang = sin(ray.radian);
	ray.tan_ang = ray.sin_ang / ray.cos_ang;
	if (-ray.sin_ang < 0)
		ray.hy = floor(data->py / GRID) * GRID - 1;
	else
		ray.hy = floor(data->py / GRID) * GRID + GRID;
	ray.hx = data->px + (data->py - ray.hy) / ray.tan_ang;
	if (ray.cos_ang < 0)
		floor(data->px / GRID) * GRID - 1;
	else
		floor(data->px / GRID) * GRID + GRID;
	ray.vy = data->py + (data->px - ray.vx) * ray.tan_ang;
	ray.next_h = fabs(GRID / ray.sin_ang);
	ray.next_v = fabs(GRID / ray.cos_ang);
	ray.dist_h = sqrt((data->px - ray.hx) * (data->px - ray.hx) +
	(data->py - ray.hy) * (data->py - ray.hy));
	ray.dist_v = sqrt((data->px - ray.vx) * (data->px - ray.vx) +
	(data->py - ray.vy) * (data->py - ray.vy));
}

int	raycasting(t_data *data)
{
	int	iter_ray;
	int	col;
	iter_ray = data->player_angle - (FOV / 2);
	col = 0;
	while (col < PLANE_WIDTH)
	{
		find_intersection(iter_ray, col, data);
		col++;
		iter_ray += RAY_ANGLE;
	}
}



int main(int ac, char **av)
{
	t_data	data;
	int		fd;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		////PARSING TEST//////////
		fd = open(av[1], O_RDONLY);
		parse_file(fd, &data);
		check_data(&data);
		//////END OF PARSING TEST/////
		find_player_location(&data);
		printf("player x %d y %d angle %d\n", data.px, data.py, data.player_angle);
	}
	else
		ft_error("Error\nwrong number of arguments\n");
}
