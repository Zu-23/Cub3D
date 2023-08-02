/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:19:46 by alemsafi          #+#    #+#             */
/*   Updated: 2023/08/02 23:28:04 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	draw_player(t_data *data)
{
	int	x;
	int	y;

	x = data->player_x - 2;
	while (x < data->player_x + 2)
	{
		y = data->player_y - 2;
		while (y < data->player_y + 2)
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

	i = x;
	while (i < (x + MAP_GRID))
	{
		j = y;
		while (j < (y + MAP_GRID))
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
	while (x < PLANE_HEIGHT / MAP_GRID)
	{
		y = 0;
		while (y < PLANE_WIDTH / MAP_GRID)
		{
			if (data->map[x][y] == '1')
				draw_square(data, (y) * MAP_GRID, (x)
					* MAP_GRID, 0x0FFFF0);
			else if (data->map[x][y] == '0' || data->map[x][y] == 'N'
					|| data->map[x][y] == 'S' || data->map[x][y] == 'E'
					|| data->map[x][y] == 'W')
				draw_square(data, (y) * MAP_GRID, (x)
					* MAP_GRID, 0x000000);
			y++;
		}
		x++;
	}
}

void	draw_sky_floor(t_data *data)
{
	int	x;
	int	y;
	int	ceiling;
	int	floor;

	x = 0;
	ceiling = data->c.red * 65536 + data->c.green * 256 + data->c.blue;
	floor = data->f.red * 65536 + data->f.green * 256 + data->f.blue;
	while (x < PLANE_HEIGHT)
	{
		y = 0;
		while (y < PLANE_WIDTH)
		{
			if (y < PLANE_WIDTH / 2)
				my_mlx_put_pixel(data, x, y, ceiling);
			else
				my_mlx_put_pixel(data, x, y, floor);
			y++;
		}
		x++;
	}
}

void	render(t_data *data)
{
	data->mlx = mlx_init();
	get_textures(data);
	data->win = mlx_new_window(data->mlx, PLANE_HEIGHT, PLANE_WIDTH, "Cub3D");
	data->img = mlx_new_image(data->mlx, PLANE_HEIGHT, PLANE_WIDTH);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	draw_sky_floor(data);
	raycasting(data);
	draw_map(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_hook(data->win, 17, 0, exit_hook, data);
	mlx_hook(data->win, 2, 0, key_hook, data);
	mlx_hook(data->win, 3, 0, key_release, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_loop(data->mlx);
}
