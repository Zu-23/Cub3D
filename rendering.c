/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:19:46 by alemsafi          #+#    #+#             */
/*   Updated: 2023/07/20 19:48:38 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
				draw_square(data, (y + 1) * 8 - 8, (x + 1) * 8 - 8, 0x00FF0000);
			else if (data->map[x][y] == '0' || data->map[x][y] == 'N'
					|| data->map[x][y] == 'S' || data->map[x][y] == 'E'
					|| data->map[x][y] == 'W')
				draw_square(data, (y + 1) * 8 - 8, (x + 1) * 8 - 8, 0x00000000);
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

void	update(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	if (data->no.img != NULL)
		(mlx_destroy_image(data->mlx, data->no.img), data->no.img = NULL);
	if (data->so.img != NULL)
		(mlx_destroy_image(data->mlx, data->so.img), data->so.img = NULL);
	if (data->we.img != NULL)
		(mlx_destroy_image(data->mlx, data->we.img), data->we.img = NULL);
	if (data->ea.img != NULL)
		(mlx_destroy_image(data->mlx, data->ea.img), data->ea.img = NULL);
	data->img = mlx_new_image(data->mlx, PLANE_HEIGHT, PLANE_WIDTH);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	draw_sky_floor(data);
	raycasting(data);
	draw_map(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	get_textures(t_data *data)
{
	data->no.img = mlx_xpm_file_to_image(data->mlx, "wall1.xpm",
			&data->no.width, &data->no.height);
	data->no.addr = mlx_get_data_addr(data->no.img, &data->no.bits_per_pixel,
			&data->no.line_length, &data->no.endian);
	data->so.img = mlx_xpm_file_to_image(data->mlx, "wall2.xpm",
			&data->so.width, &data->so.height);
	data->so.addr = mlx_get_data_addr(data->so.img, &data->so.bits_per_pixel,
			&data->so.line_length, &data->so.endian);
	data->we.img = mlx_xpm_file_to_image(data->mlx, "wall3.xpm",
			&data->we.width, &data->we.height);
	data->we.addr = mlx_get_data_addr(data->we.img, &data->we.bits_per_pixel,
			&data->we.line_length, &data->we.endian);
	data->ea.img = mlx_xpm_file_to_image(data->mlx, "wall4.xpm",
			&data->ea.width, &data->ea.height);
	data->ea.addr = mlx_get_data_addr(data->ea.img, &data->ea.bits_per_pixel,
			&data->ea.line_length, &data->ea.endian);
}

void	render(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, PLANE_HEIGHT, PLANE_WIDTH, "Cub3D");
	data->img = mlx_new_image(data->mlx, PLANE_HEIGHT, PLANE_WIDTH);
	get_textures(data);
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
