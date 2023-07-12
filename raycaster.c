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
				data->px = (var.i + 1) * GRID - 32;
				data->py = (var.j + 1) * GRID - 32;
				check_player_angle(*(ft_strchr("WESN",
							data->map[var.j][var.i])), data);
				return ;
			}
			var.i++;
		}
		var.j++;
	}
}

void	data_init(t_data *data) //might not be needed since we defined macros
{
	ft_memset(data, 0, sizeof(t_data));
	data->plane_height = 1024;
	data->plane_width = 1024;
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

void	draw_wall(int col, t_rcst *ray, t_data *data, t_wall *wall)
{
	double	wall_height;
	double	top_wall;
	double	i;

	i = 0;
	wall_height = ceil(GRID_DIV_PROJ / wall->wall_dist); // could be used in the same equation for top wall
	top_wall = PLANE_CENTER - (wall_height / 2);
	while (i < wall_height)
	{
		MLX_PUT_PIXEL(col, top_wall + i);
		i++;
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
	ray->dist_v = sqrt((data->px - ray->vx) * (data->px - ray->vx) + \
			(data->py - ray->vy) * (data->py - ray->vy));
	return (0);
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
		col++;
		iter_ray += RAY_ANGLE;
	}
	return (0);
}
