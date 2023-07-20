/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 23:55:38 by alemsafi          #+#    #+#             */
/*   Updated: 2023/07/21 00:04:25 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

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

void	my_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_color(t_texture *texture, int x, int y)
{
	int	color;

	color = *(unsigned int *)(texture->addr + (y * texture->line_length + x
				* (texture->bits_per_pixel / 8)));
	return (color);
}

void	update(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	if (!data->no.img)
		(mlx_destroy_image(data->mlx, data->no.img), data->no.img = NULL);
	if (!data->so.img)
		(mlx_destroy_image(data->mlx, data->so.img), data->so.img = NULL);
	if (!data->we.img)
		(mlx_destroy_image(data->mlx, data->we.img), data->we.img = NULL);
	if (!data->ea.img)
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