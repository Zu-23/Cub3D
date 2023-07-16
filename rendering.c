/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:19:46 by alemsafi          #+#    #+#             */
/*   Updated: 2023/07/16 15:59:21 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mlx.h>

void	my_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_player(t_data *data)
{
	int	x;
	int	y;

	x = data->px - 5;
	while (x < data->px + 5)
	{
		y = data->py - 5;
		while (y < data->py + 5)
		{
			my_mlx_put_pixel(data, x, y, 0x000000FF);
			y++;
		}
		x++;
	}
}

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = x * 1;
	while (i < (x + GRID) * 1)
	{
		j = y * 1;
		while (j < (y + GRID) * 1)
		{
			my_mlx_put_pixel(data, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < PLANE_HEIGHT)
	{
		y = 0;
		while (y < PLANE_WIDTH)
		{
			if (data->map[x][y] == '1')
				draw_square(data, (y + 1) * GRID - GRID, (x + 1) * GRID - GRID,
					0x00FF0000);
			else if (data->map[x][y] == '0' || data->map[x][y] == 'N'
					|| data->map[x][y] == 'S' || data->map[x][y] == 'E'
					|| data->map[x][y] == 'W')
				draw_square(data, (y + 1) * GRID - GRID, (x + 1) * GRID - GRID,
					0x00000000);
			y++;
		}
		x++;
	}
}

void	update(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, PLANE_HEIGHT, PLANE_WIDTH);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	draw_map(data);
	draw_player(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	key_hook(int keycode, t_data *data)
{
	int	x;
	int	y;

	x = data->px;
	y = data->py;
	if (keycode == ESC)
		exit(0);
	if (keycode == S)
	{
		data->px -= 10 * cos(data->player_angle * M_PI / 180);
		data->py -= 10 * -sin(data->player_angle * M_PI / 180);
		if (data->map[(int)(data->py / GRID)][(int)(data->px / GRID)] == '1')
		{
			data->px = x;
			data->py = y;
		}
	}
	if (keycode == W)
	{
		data->px += 10 * cos(data->player_angle * M_PI / 180);
		data->py += 10 * -sin(data->player_angle * M_PI / 180);
		if (data->map[(int)(data->py / GRID)][(int)(data->px / GRID)] == '1')
		{
			data->px = x;
			data->py = y;
		}
	}
	if (keycode == A)
	{
		data->px -= 10 * cos((data->player_angle - 90) * M_PI / 180);
		data->py -= 10 * -sin((data->player_angle - 90) * M_PI / 180);
		if (data->map[(int)(data->py / GRID)][(int)(data->px / GRID)] == '1')
		{
			data->px = x;
			data->py = y;
		}
	}
	if (keycode == D)
	{
		data->px += 10 * cos((data->player_angle - 90) * M_PI / 180);
		data->py += 10 * -sin((data->player_angle - 90) * M_PI / 180);
		if (data->map[(int)(data->py / GRID)][(int)(data->px / GRID)] == '1')
		{
			data->px = x;
			data->py = y;
		}
	}
	if (keycode == LEFT)
	{
		data->player_angle += 10;
		if (data->player_angle < 0)
			data->player_angle += 360;
	}
	if (keycode == RIGHT)
	{
		data->player_angle -= 10;
		if (data->player_angle > 360)
			data->player_angle -= 360;
	}
	update(data);
	return (0);
}

void	render(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, PLANE_HEIGHT, PLANE_WIDTH, "Cub3D");
	data->img = mlx_new_image(data->mlx, PLANE_HEIGHT, PLANE_WIDTH);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	draw_map(data);
	draw_player(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, key_hook, data);
	mlx_loop(data->mlx);
}
