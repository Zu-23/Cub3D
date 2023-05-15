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
				return;
			}
			var.i++;
		}
		var.j++;
	}
}