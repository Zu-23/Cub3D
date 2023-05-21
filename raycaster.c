#include "42-functions/LIBFT_42/libft.h"
#include "minilibx-linux/mlx.h"


//objective 1:
//locate player location

void	find_player_location(t_data *data)
{
	t_var var;

	var.j = 0;
	while (var.j < data->height)
	{
		var.i = 0;
		while (data->map[var.j][var.i])
		{
			if (ft_strchr("NSWE", data->map[var.j][var.i]))
			{
				data->px = var.i * 64 - 32;
				data->py = var.j * 64 - 32;
				check_player_angle(*(ft_strchr("NSWE", data->map[var.j][var.i])), data);
				return;
			}
			var.i++;
		}
		var.j++;
	}
}

int	data_init(t_data *data)//might not be needed since we defined macros 
{
	ft_memset(data, 0, sizeof(t_data));
	data->plane_height = 1024;
	data->plane_width = 1024;
}
//casting ray process
//1- 

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

int	raycasting(t_data *data)
{
	int	start_ray;
	int	i;
	iter_ray = data->player_angle - (FOV / 2);
	i = 0;
	while (i < PLANE_WIDTH)
	{
		iter_ray += RAY_ANGLE;
	}
}