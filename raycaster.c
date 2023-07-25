/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:34:45 by alemsafi          #+#    #+#             */
/*   Updated: 2023/07/25 18:37:17 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (ft_strchr("ESNW", data->map[var.j][var.i]))
			{
				data->px = (var.i) * GRID + GRID / 2;
				data->py = (var.j) * GRID + GRID / 2;
				data->player_x = (var.i) * MAP_GRID + MAP_GRID / 2;
				data->player_y = (var.j) * MAP_GRID + MAP_GRID / 2;
				check_player_angle(*(ft_strchr("ESNW",
							data->map[var.j][var.i])), data);
				return ;
			}
			var.i++;
		}
		var.j++;
	}
}

void	init(double *wall_height, double *top_wall, double *shift, t_wall *wall)
{
	*shift = 0;
	if (wall->wall_dist < 0.001)
		wall->wall_dist = 0.001;
	*wall_height = ceil((double)GRID / wall->wall_dist * PLAYER_DISTANCE);
	*top_wall = PLANE_CENTER - (*wall_height / 2);
	if (*top_wall < 0)
	{
		*shift = -(*top_wall);
		*top_wall = 0;
	}
}

void	draw_wall(int col, t_rcst *ray, t_data *data, t_wall *wall)
{
	double	wall_height;
	double	top_wall;
	double	i;
	double	shift;

	(init(&wall_height, &top_wall, &shift, wall), (i = -1));
	while (++i <= wall_height && top_wall + i < PLANE_HEIGHT)
	{
		if (ray->dist_h <= ray->dist_v && ray->sin_ang < 0)
			my_mlx_put_pixel(data, col, top_wall + i, get_color(&data->so,
					(int)(wall->wall_x * TEXTURE_SCALE) % data->so.width, (int)
					(((i + shift) / wall_height) * data->so.height)));
		else if (ray->dist_h <= ray->dist_v && ray->sin_ang > 0)
			my_mlx_put_pixel(data, col, top_wall + i, get_color(&data->no,
					(int)(wall->wall_x * TEXTURE_SCALE) % data->no.width, (int)
					(((i + shift) / wall_height) * data->no.height)));
		else if (ray->dist_h > ray->dist_v && ray->cos_ang < 0)
			my_mlx_put_pixel(data, col, top_wall + i, get_color(&data->ea,
					(int)(wall->wall_y * TEXTURE_SCALE) % data->ea.width, (int)
					(((i + shift) / wall_height) * data->ea.height)));
		else if (ray->dist_h > ray->dist_v && ray->cos_ang > 0)
			my_mlx_put_pixel(data, col, top_wall + i, get_color(&data->we,
					(int)(wall->wall_y * TEXTURE_SCALE) % data->we.width, (int)
					(((i + shift) / wall_height) * data->we.height)));
	}
}

// void	draw_ray(t_data *data, t_wall wall)
// {
// 	double	slope;
// 	double	y_intercept;
// 	double	px;
// 	double	py;
// 	double	tmp;
// 	double	wall_x;
// 	double	wall_y;

// 	px = (double)data->px;
// 	py = (double)data->py;
// 	wall_x = wall.wall_x;
// 	wall_y = wall.wall_y;
// 	slope = (data->py - wall.wall_y) / (data->px - wall.wall_x);
// 	y_intercept = data->py - slope * data->px;
// 	if (px >= wall_x)
// 	{
// 		tmp = px;
// 		px = wall_x;
// 		wall_x = tmp;
// 		tmp = py;
// 		py = wall_y;
// 		wall_y = tmp;
// 	}
// 	while (px <= wall_x)
// 	{
// 		my_mlx_put_pixel(data, px, slope * px + y_intercept, 0x00FF00);
// 		px++;
// 	}
// }

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
		col++;
		iter_ray -= RAY_ANGLE - RAY_ANGLE * 0.01;
	}
	return (0);
}
