/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:56:49 by alemsafi          #+#    #+#             */
/*   Updated: 2023/07/25 18:56:50 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("player x %d player y %d\n", data.px, data.py);
		printf("player angle %d\n", data.player_angle);
		render(&data);
	}
	else
		ft_error("Error\nwrong number of arguments\n");
}
