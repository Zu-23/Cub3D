/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:31:49 by zhaddoum          #+#    #+#             */
/*   Updated: 2023/08/02 23:26:25 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	coom_counter(char *line)
{
	int	i;
	int	coom;
	int	state;

	i = -1;
	coom = 0;
	state = 0;
	while (line[++i] && line[i] != '\n')
	{
		if (state && ft_isspace(line[i - 1]) && ft_isdigit(line[i]))
			ft_error("u hav been coomed(comas)\n");
		if (coom == 2 && !ft_isspace(line[i]) && !ft_isdigit(line[i]))
			(printf("%d\n", line[i]), ft_error("u hav been coomed(comas)\n"));
		while (line[i] != '\n' && ft_isdigit(line[i]) && ++i)
			state = 1;
		if (line[i] == ',')
		{
			if (state && ++coom)
				state--;
			else
				ft_error("u hav been coomed(comas)\n");
		}
	}
	return (coom);
}

int	fill_color(char *line, t_color *color, int *success)
{
	char	*rgb[3];
	int		i;

	i = 0;
	if (color->id[0] != '\0')
		return (-1);
	if (coom_counter(line) != 2)
		ft_error("u hav been coomed(comas)\n");
	ft_strcpy(color->id, ft_strtok(line, " "));
	while (i < 3)
	{
		rgb[i] = ft_strtok(NULL, " ,\n");
		if (check_rgb(rgb[i++]))
			return (-1);
	}
	color->red = ft_atoi(rgb[0]);
	color->green = ft_atoi(rgb[1]);
	color->blue = ft_atoi(rgb[2]);
	if ((color->red < 0 || color->red > 255) || (color->green < 0
			|| color->green > 255) || (color->blue < 0 || color->blue > 255))
		return (-1);
	*success = 1;
	return (0);
}

int	parse_texture(char *line, t_data *data, int *success)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		if (fill_texture(line, &data->no, success))
			return (-1);
	}
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		if (fill_texture(line, &data->so, success))
			return (-1);
	}
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		if (fill_texture(line, &data->ea, success))
			return (-1);
	}
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		if (fill_texture(line, &data->we, success))
			return (-1);
	}
	return (0);
}

int	check_valid_line(char *line, t_data *data)
{
	char	*content;
	int		i;
	int		j;

	i = 0;
	j = 0;
	content = "01ESNW ";
	if (!data->ea.id[0] || !data->no.id[0] || !data->so.id[0] || !data->we.id[0]
		|| !data->c.id[0] || !data->f.id[0])
		return (-1);
	while (line[j] && line[j] != '\n')
	{
		while (line[j] == ' ')
			j++;
		while (content[i] && content[i++] != line[j])
			;
		if (content[i] == '\0')
			return (-1);
		i = 0;
		j++;
	}
	return (0);
}

int	check_closed_walls(t_data *data)
{
	int		startrow;
	int		startcol;
	int		i;
	size_t	j;

	i = -1;
	startrow = -1;
	startcol = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < ft_strlen(data->map[i]))
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W'
				|| data->map[i][j] == '0')
			{
				startrow = i;
				startcol = j;
				if (backtrack(data, startrow, startcol))
					return (-1);
			}
		}
	}
	return (0);
}
