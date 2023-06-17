#include "Cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		parse_file(fd, &data);
		check_data(&data);
		find_player_location(&data);
		printf("player x %d y %d angle %d\n", data.px, data.py, data.player_angle);
	}
	else
		ft_error("Error\nwrong number of arguments\n");
}
