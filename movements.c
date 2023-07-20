/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:31:29 by alemsafi          #+#    #+#             */
/*   Updated: 2023/07/20 19:53:23 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	move_backwards(t_data *data, int x, int y)
{
	int	x2;
	int	y2;

	x2 = data->player_x;
	y2 = data->player_y;
	data->px -= 10 * cos(data->player_angle * M_PI / 180);
	data->py -= 10 * -sin(data->player_angle * M_PI / 180);
	data->player_x -= (80 / GRID) * cos(data->player_angle * M_PI / 180);
	data->player_y -= (80 / GRID) * -sin(data->player_angle * M_PI / 180);
	if (data->map[(int)((data->py + 1) / GRID)][(int)((data->px + 1)
			/ GRID)] == '1' || data->map[(int)((data->py - 1)
			/ GRID)][(int)((data->px - 1) / GRID)] == '1')
	{
		data->px = x;
		data->py = y;
		data->player_x = x2;
		data->player_y = y2;
	}
}

void	move_forward(t_data *data, int x, int y)
{
	int	x2;
	int	y2;

	x2 = data->player_x;
	y2 = data->player_y;
	data->px += 10 * cos(data->player_angle * M_PI / 180);
	data->py += 10 * -sin(data->player_angle * M_PI / 180);
	data->player_x += (80 / GRID) * cos(data->player_angle * M_PI / 180);
	data->player_y += (80 / GRID) * -sin(data->player_angle * M_PI / 180);
	if (data->map[(int)((data->py + 1) / GRID)][(int)((data->px + 1)
			/ GRID)] == '1' || data->map[(int)((data->py - 1)
			/ GRID)][(int)((data->px - 1) / GRID)] == '1')
	{
		data->px = x;
		data->py = y;
		data->player_x = x2;
		data->player_y = y2;
	}
}

void	move_left(t_data *data, int x, int y)
{
	int	x2;
	int	y2;

	x2 = data->player_x;
	y2 = data->player_y;
	data->px -= 10 * cos((data->player_angle - 90) * M_PI / 180);
	data->py -= 10 * -sin((data->player_angle - 90) * M_PI / 180);
	data->player_x -= (80 / GRID) * cos((data->player_angle - 90) * M_PI / 180);
	data->player_y -= (80 / GRID) * -sin((data->player_angle - 90) * M_PI
			/ 180);
	if (data->map[(int)((data->py + 1) / GRID)][(int)((data->px + 1)
			/ GRID)] == '1' || data->map[(int)((data->py - 1)
			/ GRID)][(int)((data->px - 1) / GRID)] == '1')
	{
		data->px = x;
		data->py = y;
		data->player_x = x2;
		data->player_y = y2;
	}
}

void	move_right(t_data *data, int x, int y)
{
	int	x2;
	int	y2;

	x2 = data->player_x;
	y2 = data->player_y;
	data->px += 10 * cos((data->player_angle - 90) * M_PI / 180);
	data->py += 10 * -sin((data->player_angle - 90) * M_PI / 180);
	data->player_x += (80 / GRID) * cos((data->player_angle - 90) * M_PI / 180);
	data->player_y += (80 / GRID) * -sin((data->player_angle - 90) * M_PI
			/ 180);
	if (data->map[(int)((data->py + 1) / GRID)][(int)((data->px + 1)
			/ GRID)] == '1' || data->map[(int)((data->py - 1)
			/ GRID)][(int)((data->px - 1) / GRID)] == '1')
	{
		data->px = x;
		data->py = y;
		data->player_x = x2;
		data->player_y = y2;
	}
}

void	turn_left(t_data *data)
{
	data->player_angle += 5;
	if (data->player_angle < 0)
		data->player_angle += 360;
}
