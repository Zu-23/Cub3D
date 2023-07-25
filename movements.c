/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 21:31:29 by alemsafi          #+#    #+#             */
/*   Updated: 2023/07/25 16:53:00 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	move_backwards(t_data *data, int x, int y)
{
	data->px -= 10 * cos((double)data->player_angle * M_PI / 180.0);
	data->py -= 10 * -sin((double)data->player_angle * M_PI / 180.0);
	data->player_x = data->px / (GRID / MAP_GRID);
	data->player_y = data->py / (GRID / MAP_GRID);
	if (data->map[(int)((data->py - 7) / GRID)][(int)((data->px + 7)
			/ GRID)] == '1' || data->map[(int)((data->py + 7)
			/ GRID)][(int)((data->px - 7) / GRID)] == '1'
		|| data->map[(int)((data->py + 7) / GRID)][(int)((data->px + 7)
			/ GRID)] == '1' || data->map[(int)((data->py - 7)
			/ GRID)][(int)((data->px - 7) / GRID)] == '1'
		|| data->map[(int)((data->py - 15) / GRID)][(int)((data->px + 15)
			/ GRID)] == '1' || data->map[(int)((data->py + 15)
			/ GRID)][(int)((data->px - 15) / GRID)] == '1'
		|| data->map[(int)((data->py + 15) / GRID)][(int)((data->px + 15)
			/ GRID)] == '1' || data->map[(int)((data->py - 15)
			/ GRID)][(int)((data->px - 15) / GRID)] == '1')
	{
		data->px = x;
		data->py = y;
		data->player_x = data->px / (GRID / MAP_GRID);
		data->player_y = data->py / (GRID / MAP_GRID);
	}
}

void	move_forward(t_data *data, int x, int y)
{
	data->px += 10 * cos((double)data->player_angle * M_PI / 180.0);
	data->py += 10 * -sin((double)data->player_angle * M_PI / 180.0);
	data->player_x = data->px / (GRID / MAP_GRID);
	data->player_y = data->py / (GRID / MAP_GRID);
	if (data->map[(int)((data->py - 7) / GRID)][(int)((data->px + 7)
			/ GRID)] == '1' || data->map[(int)((data->py + 7)
			/ GRID)][(int)((data->px - 7) / GRID)] == '1'
		|| data->map[(int)((data->py + 7) / GRID)][(int)((data->px + 7)
			/ GRID)] == '1' || data->map[(int)((data->py - 7)
			/ GRID)][(int)((data->px - 7) / GRID)] == '1'
		|| data->map[(int)((data->py - 15) / GRID)][(int)((data->px + 15)
			/ GRID)] == '1' || data->map[(int)((data->py + 15)
			/ GRID)][(int)((data->px - 15) / GRID)] == '1'
		|| data->map[(int)((data->py + 15) / GRID)][(int)((data->px + 15)
			/ GRID)] == '1' || data->map[(int)((data->py - 15)
			/ GRID)][(int)((data->px - 15) / GRID)] == '1')
	{
		data->px = x;
		data->py = y;
		data->player_x = data->px / (GRID / MAP_GRID);
		data->player_y = data->py / (GRID / MAP_GRID);
	}
}

void	move_left(t_data *data, int x, int y)
{
	data->px -= 10 * cos((double)(data->player_angle - 90) * M_PI / 180.0);
	data->py -= 10 * -sin((double)(data->player_angle - 90) * M_PI / 180.0);
	data->player_x = data->px / (GRID / MAP_GRID);
	data->player_y = data->py / (GRID / MAP_GRID);
	if (data->map[(int)((data->py - 7) / GRID)][(int)((data->px + 7)
			/ GRID)] == '1' || data->map[(int)((data->py + 7)
			/ GRID)][(int)((data->px - 7) / GRID)] == '1'
		|| data->map[(int)((data->py + 7) / GRID)][(int)((data->px + 7)
			/ GRID)] == '1' || data->map[(int)((data->py - 7)
			/ GRID)][(int)((data->px - 7) / GRID)] == '1'
		|| data->map[(int)((data->py - 15) / GRID)][(int)((data->px + 15)
			/ GRID)] == '1' || data->map[(int)((data->py + 15)
			/ GRID)][(int)((data->px - 15) / GRID)] == '1'
		|| data->map[(int)((data->py + 15) / GRID)][(int)((data->px + 15)
			/ GRID)] == '1' || data->map[(int)((data->py - 15)
			/ GRID)][(int)((data->px - 15) / GRID)] == '1')
	{
		data->px = x;
		data->py = y;
		data->player_x = data->px / (GRID / MAP_GRID);
		data->player_y = data->py / (GRID / MAP_GRID);
	}
}

void	move_right(t_data *data, int x, int y)
{
	data->px += 10 * cos((double)(data->player_angle - 90) * M_PI / 180.0);
	data->py += 10 * -sin((double)(data->player_angle - 90) * M_PI / 180.0);
	data->player_x = data->px / (GRID / MAP_GRID);
	data->player_y = data->py / (GRID / MAP_GRID);
	if (data->map[(int)((data->py - 7) / GRID)][(int)((data->px + 7)
			/ GRID)] == '1' || data->map[(int)((data->py + 7)
			/ GRID)][(int)((data->px - 7) / GRID)] == '1'
		|| data->map[(int)((data->py + 7) / GRID)][(int)((data->px + 7)
			/ GRID)] == '1' || data->map[(int)((data->py - 7)
			/ GRID)][(int)((data->px - 7) / GRID)] == '1'
		|| data->map[(int)((data->py - 15) / GRID)][(int)((data->px + 15)
			/ GRID)] == '1' || data->map[(int)((data->py + 15)
			/ GRID)][(int)((data->px - 15) / GRID)] == '1'
		|| data->map[(int)((data->py + 15) / GRID)][(int)((data->px + 15)
			/ GRID)] == '1' || data->map[(int)((data->py - 15)
			/ GRID)][(int)((data->px - 15) / GRID)] == '1')
	{
		data->px = x;
		data->py = y;
		data->player_x = data->px / (GRID / MAP_GRID);
		data->player_y = data->py / (GRID / MAP_GRID);
	}
}

void	turn_left(t_data *data)
{
	data->player_angle += 10;
	if (data->player_angle < 0)
		data->player_angle += 360;
}
