/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:31:49 by zhaddoum          #+#    #+#             */
/*   Updated: 2023/08/02 16:09:49 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

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
			ft_error("bruh");
		if (coom == 2 && !ft_isspace(line[i]) && !ft_isdigit(line[i]))
			(printf("%d\n", line[i]), ft_error("get_ccomec"));
		while (line[i] != '\n' && ft_isdigit(line[i]) && ++i)
			state = 1;
		if (line[i] == ',')
		{
			if (state && ++coom)
				state--;
			else
				ft_error("coomed\n");
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
		ft_error("u have bee coomned\n");
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
	printf("%s\n", line);
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
	while (++i < data->height && startrow == -1 && startcol == -1)
	{
		j = -1;
		while (++j < ft_strlen(data->map[i]))
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				startrow = i;
				startcol = j;
				break ;
			}
		}
	}
	if (backtrack(data, startrow, startcol))
		return (-1);
	return (0);
}

void	check_data(t_data *data)
{
	if (!data->ea.id[0] || !data->no.id[0] || !data->so.id[0]
		|| !data->we.id[0])
		ft_error("Error\nincorrect walls texture inputs\n");
	if (!data->c.id[0] || !data->f.id[0])
		ft_error("Error\nincorrect floor or ceiling inputs\n");
	if (check_map(data))
		ft_error("Error\nincorrect map inputs\n");
}
