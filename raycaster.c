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

t_rcst	*find_intersection(int iter_ray, int column, t_data *data)
{
	t_rcst	*ray;

	ray->radian = iter_ray * 3.14 / 180.0 - atan((PLANE_WIDTH / 2 - column)
			/ PLAYER_DISTANCE);
	ray->cos_ang = cos(ray->radian);
	ray->sin_ang = sin(ray->radian);
	ray->tan_ang = ray->sin_ang / ray->cos_ang;
	if (-ray->sin_ang < 0)
		ray->hy = floor(data->py / GRID) * GRID - 1;
	else
		ray->hy = floor(data->py / GRID) * GRID + GRID;
	ray->hx = data->px + (data->py - ray->hy) / ray->tan_ang;
	if (ray->cos_ang < 0)
		ray->hx = floor(data->px / GRID) * GRID - 1;
	else
		ray->hx = floor(data->px / GRID) * GRID + GRID;
	ray->vy = data->py + (data->px - ray->vx) * ray->tan_ang;
	ray->next_h = fabs(GRID / ray->sin_ang);
	ray->next_v = fabs(GRID / ray->cos_ang);
	ray->dist_h = sqrt((data->px - ray->hx) * (data->px - ray->hx) + \
		(data->py - ray->hy) * (data->py - ray->hy));
	ray->dist_v = sqrt((data->px - ray->vx) * (data->px - ray->vx) + \
		(data->py - ray->vy) * (data->py - ray->vy));
	return (ray);
}

void	raycasting(t_data *data)
{
	int		iter_ray;
	int		col;
	t_rcst	*ray;

	iter_ray = data->player_angle - (FOV / 2);
	col = 0;
	while (col < PLANE_WIDTH)
	{
		ray = find_intersection(iter_ray, col, data);
		//draw_ray(ray, col, data);
		col++;
		iter_ray += RAY_ANGLE;
	}
}
