/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:32:26 by alemsafi          #+#    #+#             */
/*   Updated: 2023/08/06 00:29:32 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	turn_right(t_data *data)
{
	data->player_angle -= 5;
	if (data->player_angle > 360)
		data->player_angle -= 360;
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == S)
		data->down = 1;
	if (keycode == W)
		data->up = 1;
	if (keycode == A)
		data->left = 1;
	if (keycode == D)
		data->right = 1;
	if (keycode == LEFT)
		data->turn_left = 1;
	if (keycode == RIGHT)
		data->turn_right = 1;
	return (0);
}

int	exit_hook(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == S)
		data->down = 0;
	if (keycode == W)
		data->up = 0;
	if (keycode == A)
		data->left = 0;
	if (keycode == D)
		data->right = 0;
	if (keycode == LEFT)
		data->turn_left = 0;
	if (keycode == RIGHT)
		data->turn_right = 0;
	return (0);
}

int	loop_hook(t_data *data)
{
	if (data->up == 1)
		move_forward(data, data->px, data->py);
	if (data->down == 1)
		move_backwards(data, data->px, data->py);
	if (data->left == 1)
		move_left(data, data->px, data->py);
	if (data->right == 1)
		move_right(data, data->px, data->py);
	if (data->turn_left == 1)
		turn_left(data);
	if (data->turn_right == 1)
		turn_right(data);
	update(data);
	return (0);
}
