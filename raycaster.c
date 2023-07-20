#include "Cub3d.h"

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
	t_var	var;

	var.j = 0;
	while (var.j < data->height)
	{
		var.i = 0;
		while (data->map[var.j][var.i])
		{
			if (ft_strchr("WESN", data->map[var.j][var.i]))
			{
				data->px = (var.i + 1) * GRID - GRID;
				data->py = (var.j + 1) * GRID - GRID;
				data->player_x = (double)(var.i + 1) *8.0 - 8.0;
				data->player_y = (double)(var.j + 1) *8.0 - 8.0;
				check_player_angle(*(ft_strchr("WESN",
							data->map[var.j][var.i])), data);
				return ;
			}
			var.i++;
		}
		var.j++;
	}
}

int	check_wall_collision(t_data *data, t_rcst *ray, t_wall *wall, int col)
{
	wall->hit = 0;
	while (wall->hit == 0)
	{
		if (ray->dist_h <= ray->dist_v)
		{
			if (data->map[(int)ray->hy / GRID][(int)ray->hx / GRID] == '1')
			{
				wall->hit = 1;
				wall->wall_x = ray->hx;
				wall->wall_y = ray->hy;
				wall->wall_dist = ray->dist_h * cos(data->player_angle * M_PI / 180 - ray->radian);
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
				wall->wall_x = ray->vx;
				wall->wall_y = ray->vy;
				wall->wall_dist = ray->dist_v * cos(data->player_angle * M_PI / 180 - ray->radian);
			}
			else
			{
				ray->dist_v += ray->next_v;
				ray->vx += ray->next_v * ray->cos_ang;
				ray->vy += ray->next_v * -ray->sin_ang;
			}
		}
	}
	return (0);
}

int	get_color(t_texture *texture, int x, int y)
{
	int	color;

	color = *(unsigned int *)(texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
	return (color);
}

void	draw_wall(int col, t_rcst *ray, t_data *data, t_wall *wall)
{
	double	wall_height;
	double	top_wall;
	double	i;

	i = 0;
	(void) col;
	(void) ray;
	if (wall->wall_dist < 0.001)
		wall->wall_dist = 0.001;
	wall_height = ceil((double)GRID / wall->wall_dist * PLAYER_DISTANCE);
	if (wall_height >= PLANE_HEIGHT)
		wall_height = PLANE_HEIGHT - 1;
	top_wall = PLANE_CENTER - (wall_height / 2);
	while (i <= wall_height && top_wall + i < PLANE_HEIGHT)
	{
		if (ray->dist_h <= ray->dist_v && ray->sin_ang < 0)
			my_mlx_put_pixel(data, col, top_wall + i, get_color(&data->so, (int)(wall->wall_x * 16) % data->so.width, (int)((i / wall_height) * data->so.height)));
		else if (ray->dist_h <= ray->dist_v && ray->sin_ang > 0)
			my_mlx_put_pixel(data, col, top_wall + i, get_color(&data->no, (int)(wall->wall_x * 16) % data->no.width, (int)((i / wall_height) * data->no.height)));
		else if (ray->dist_h > ray->dist_v && ray->cos_ang < 0)
			my_mlx_put_pixel(data, col, top_wall + i, get_color(&data->ea, (int)(wall->wall_y * 16) % data->ea.width, (int)((i / wall_height) * data->ea.height)));
		else if (ray->dist_h > ray->dist_v && ray->cos_ang > 0)
			my_mlx_put_pixel(data, col, top_wall + i, get_color(&data->we, (int)(wall->wall_y * 16) % data->we.width, (int)((i / wall_height) * data->we.height)));
		i++;
	}
}

int	find_intersection(double iter_ray, int column, t_data *data, t_rcst *ray)
{
	ray->radian = iter_ray * (3.14 / 180.0) + 0.0001;
	ray->cos_ang = cos(ray->radian);
	ray->sin_ang = sin(ray->radian);
	if (ray->cos_ang == 0)
		ray->cos_ang = 0.001;
	ray->tan_ang = ray->sin_ang / ray->cos_ang;
	if (-ray->sin_ang < 0)
		ray->hy = (data->py / GRID) * GRID - 0.001;
	else
		ray->hy = (data->py / GRID) * GRID + GRID;
	ray->hx = data->px + (data->py - ray->hy) / ray->tan_ang;
	if (ray->cos_ang < 0)
		ray->vx = (data->px / GRID) * GRID - 0.001;
	else
		ray->vx = (data->px / GRID) * GRID + GRID;
	ray->vy = data->py + (data->px - ray->vx) * ray->tan_ang;
	ray->next_h = fabs(GRID / ray->sin_ang);
	ray->next_v = fabs(GRID / ray->cos_ang);
	ray->dist_h = sqrt((data->px - ray->hx) * (data->px - ray->hx) + \
			(data->py - ray->hy) * (data->py - ray->hy));
	ray->dist_v = sqrt((data->px - ray->vx) * (data->px - ray->vx) + \
			(data->py - ray->vy) * (data->py - ray->vy));
	return (0);
}

void	draw_ray(t_data *data, t_wall wall)
{
	double	slope;
	double	y_intercept;
	double	px;
	double	py;
	double	tmp;
	double	wall_x;
	double	wall_y;

	px = (double)data->px;
	py = (double)data->py;
	wall_x = wall.wall_x;
	wall_y = wall.wall_y;
	slope = (data->py - wall.wall_y) / (data->px - wall.wall_x);
	y_intercept = data->py - slope * data->px;
	if (px >= wall_x)
	{
		tmp = px;
		px = wall_x;
		wall_x = tmp;
		tmp = py;
		py = wall_y;
		wall_y = tmp;
	}
	while (px <= wall_x)
	{
		my_mlx_put_pixel(data, px, slope * px + y_intercept, 0x00FF00);
		px++;
	}
}

int	raycasting(t_data *data)
{
	double	iter_ray;
	int		col;
	t_rcst	ray;
	t_wall	wall;

	iter_ray = data->player_angle + (FOV / 2);
	col = 0;
	while (col < PLANE_WIDTH)
	{
		find_intersection(iter_ray, col, data, &ray);
		check_wall_collision(data, &ray, &wall, col);
		draw_wall(col, &ray, data, &wall);
		//draw_ray(data, wall);
		col++;
		iter_ray -= RAY_ANGLE - RAY_ANGLE * 0.01;
	}
	return (0);
}
