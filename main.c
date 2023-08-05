/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:56:49 by alemsafi          #+#    #+#             */
/*   Updated: 2023/08/06 00:23:26 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	parse_textures(t_data *data)
{
	int	i;

	i = open(data->no.dest, O_RDONLY);
	if (i == -1)
		ft_error("Error\nwrong north texture path\n");
	i = open(data->so.dest, O_RDONLY);
	if (i == -1)
		ft_error("Error\nwrong south texture path\n");
	i = open(data->ea.dest, O_RDONLY);
	if (i == -1)
		ft_error("Error\nwrong east texture path\n");
	i = open(data->we.dest, O_RDONLY);
	if (i == -1)
		ft_error("Error\nwrong west texture path\n");
}

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
			ft_error("Error\nwrong file extension\n");
		fd = open(av[1], O_RDONLY);
		parse_file(fd, &data);
		check_data(&data);
		find_player_location(&data);
		parse_textures(&data);
		render(&data);
	}
	else
		ft_error("Error\nwrong number of arguments\n");
	return (0);
}
