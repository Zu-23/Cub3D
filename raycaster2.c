/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhaddoum <zhaddoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:35:27 by alemsafi          #+#    #+#             */
/*   Updated: 2023/08/07 16:16:56 by zhaddoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	find_intersection(double iter_ray, int column, t_data *data, t_rcst *ray)
{
	(void)column;
	ray->radian = iter_ray * (3.14 / 180.0) + 0.0001;
	ray->cos_ang = cos(ray->radian);
	ray->sin_ang = sin(ray->radian);
	if (ray->cos_ang == 0)
		ray->cos_ang = 0.001;
	ray->tan_ang = ray->sin_ang / ray->cos_ang;
	if (-ray->sin_ang < 0)
		ray->hy = ((int)data->py / GRID) * GRID - 0.001;
	else
		ray->hy = ((int)data->py / GRID) * GRID + GRID;
	ray->hx = data->px + (data->py - ray->hy) / ray->tan_ang;
	if (ray->cos_ang < 0)
		ray->vx = ((int)data->px / GRID) * GRID - 0.001;
	else
		ray->vx = ((int)data->px / GRID) * GRID + GRID;
	ray->vy = data->py + (data->px - ray->vx) * ray->tan_ang;
	ray->next_h = fabs(GRID / ray->sin_ang);
	ray->next_v = fabs(GRID / ray->cos_ang);
	ray->dist_h = sqrt((data->px - ray->hx) * (data->px - ray->hx) + \
						(data->py - ray->hy) * (data->py - ray->hy));
	ray->dist_v = sqrt((data->px - ray->vx) * (data->px - ray->vx) + \
						(data->py - ray->vy) * (data->py - ray->vy));
	return (0);
}

void	horizontal_intersection(t_data *data, t_rcst *ray, t_wall *wall)
{
	if ((int)ray->hy / GRID >= data->height)
		ray->hy = (data->height - 1) * GRID;
	if ((int)ray->hx / GRID >= (int)ft_strlen(data->map[(int)ray->hy / GRID]))
		ray->hx = (ft_strlen(data->map[(int)ray->hy / GRID]) - 1) * GRID;
	if (data->map[(int)ray->hy / GRID][(int)ray->hx / GRID] == '1' ||
		data->map[(int)ray->hy / GRID][(int)ray->hx / GRID] == ' ')
	{
		wall->hit = 1;
		wall->wall_x = ray->hx;
		wall->wall_y = ray->hy;
		wall->wall_dist = ray->dist_h * cos(data->player_angle * M_PI
				/ 180 - ray->radian);
	}
	else
	{
		ray->dist_h += ray->next_h;
		ray->hx += ray->next_h * ray->cos_ang;
		ray->hy += ray->next_h * -ray->sin_ang;
	}
}

void	vertical_intersection(t_data *data, t_rcst *ray, t_wall *wall)
{
	if ((int)ray->vy / GRID >= data->height)
		ray->vy = (data->height - 1) * GRID;
	if ((int)ray->vx / GRID >= (int)ft_strlen(data->map[(int)ray->vy / GRID]))
		ray->vx = (ft_strlen(data->map[(int)ray->vy / GRID]) - 1) * GRID;
	if (data->map[(int)ray->vy / GRID][(int)ray->vx / GRID] == '1' ||
		data->map[(int)ray->vy / GRID][(int)ray->vx / GRID] == ' ')
	{
		wall->hit = 1;
		wall->wall_x = ray->vx;
		wall->wall_y = ray->vy;
		wall->wall_dist = ray->dist_v * cos(data->player_angle * M_PI
				/ 180 - ray->radian);
	}
	else
	{
		ray->dist_v += ray->next_v;
		ray->vx += ray->next_v * ray->cos_ang;
		ray->vy += ray->next_v * -ray->sin_ang;
	}
}

int	check_wall_collision(t_data *data, t_rcst *ray, t_wall *wall, int col)
{
	(void)col;
	wall->hit = 0;
	while (wall->hit == 0)
	{
		if (ray->dist_h <= ray->dist_v)
			horizontal_intersection(data, ray, wall);
		else
			vertical_intersection(data, ray, wall);
	}
	return (0);
}
