#include "Cub3d.h"

int	ft_error(char *str)
{
	perror(str);
	exit(1);
}

int	ft_isspace(int c)
{
	return ((c == '\f') || (c == '\r') || (c == '\t') || (c == '\v'));
}

int	fill_texture(char *line, t_texture *texture, int *success)
{
	char	*after_xpm;

	after_xpm = ft_strstr(line, ".xpm") + 4;
	while (after_xpm != (char *)4 && *after_xpm != '\n')
	{
		if (*after_xpm != ' ')
			return (-1);
		after_xpm++;
	}
	if (texture->id[0] != '\0')
		return (-1);
	ft_strcpy(texture->id, ft_strtok(line, " "));
	ft_strcpy(texture->dest, ft_strtok(NULL, " \n\r\f\t\v"));
	printf("id: %s\ndest: %s\n", texture->id, texture->dest);
	if (!texture->dest || ft_strstr(texture->dest, ".xpm") == NULL)
		return (-1);
	*success = 1;
	return (0);
}

int	check_rgb(char *rgb)
{
	int	i;

	i = 0;
	//printf("RGB: %s\n", rgb);
	if (rgb == NULL)
		return (-1);
	while (rgb[i])
	{
		if (ft_isdigit(rgb[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	fill_color(char *line, t_color *color, int *success)
{
	char	*rgb[3];
	int		i;

	i = 0;
	if (color->id[0] != '\0')
		return (-1);
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
	printf("id %s red %d green %d blue %d\n", color->id, color->red,
			color->green, color->blue);
	return (0);
}

int	parse_color(char *line, t_data *data, int *success)
{
	if (line[0] == 'C' && line[1] == ' ')
	{
		if (fill_color(line, &data->c, success))
			return (-1);
	}
	else if (line[0] == 'F' && line[1] == ' ')
	{
		if (fill_color(line, &data->f, success))
			return (-1);
	}
	return (0);
}

int	parse_texture(char *line, t_data *data, int *success)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		if (fill_texture(line, &data->no, success))
			return (-1);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		if (fill_texture(line, &data->so, success))
			return (-1);
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if (fill_texture(line, &data->ea, success))
			return (-1);
	}
	else if (line[0] == 'W' && line[1] == 'E')
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
	content = "01WESN ";
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

int	parse_map(char *line, t_data *data, char *content)
{
	char	*str;
	t_var	var;
	int		len;

	var.i = 0;
	var.j = 0;
	var.k = 0;
	if (check_valid_line(line, data))
		return (-1);
	str = malloc(ft_strlen(line) + 1);
	if (!str)
		return (-1);
	len = ft_strlen(line);
	while (line[var.i] && line[var.i] != '\n')
	{
		while (line[var.i] == ' ' && var.i++)
			str[var.j++] = '0';
		str[var.j++] = line[var.i++];
	}
	str[var.j] = '\0';
	ft_strcpy(data->map[data->height++], str);
	// printf("map: %s\n", data->map[data->height-1]);
	free(str);
	return (0);
}

int	evaluate_parse_functions(char *line, t_data *data)
{
	int	success;

	success = 0;
	if (line[0] == '\n')
		return (0);
	if (parse_texture(line, data, &success))
		return (-1);
	if (success == 1)
		return (0);
	if (parse_color(line, data, &success))
		return (-1);
	if (success == 1)
		return (0);
	if (parse_map(line, data, "01WESN "))
		return (-1);
	return (0);
}

int	parse_file(int fd, t_data *data)
{
	int		error;
	char	*line;

	error = 0;
	line = get_next_line(fd);
	if (line == NULL)
		ft_error("Error\nin file handling\n");
	while (line)
	{
		if (evaluate_parse_functions(line, data))
		{
			error = -2;
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (error)
		ft_error("Error\nin file parsing\n");
	return (0);
}

int	check_player_position(t_data *data)
{
	t_var	var;
	int		p_pos;

	var.i = 0;
	var.j = 0;
	p_pos = 0;
	while (var.j < data->height)
	{
		while (data->map[var.j][var.i])
		{
			if (data->map[var.j][var.i] != '0'
				&& data->map[var.j][var.i] != '1')
			{
				if (p_pos == 0)
					p_pos = 1;
				else
					return (-1);
			}
			var.i++;
		}
		var.j++;
		var.i = 0;
	}
	return (0);
}

// int	check_closed_walls(t_data *data)
// {
// 	t_var	var;

// 	var.i = 0;
// 	var.j = 0;
// 	while (data->map[0][var.i])
// 	{
// 		if (data->map[0][var.i++] != '1')
// 			return (-1);
// 	}
// 	var.i = 0;
// 	while (data->map[data->height - 1][var.i])
// 	{
// 		if (data->map[data->height - 1][var.i++] != '1')
// 			return (-1);
// 	}
// 	while (var.j < data->height)
// 	{
// 		if (data->map[var.j][0] != '1'
// 			|| data->map[var.j][ft_strlen(data->map[var.j]) - 1] != '1')
// 			return (-1);
// 		var.j++;
// 	}
// 	return (0);
// }

int	backtrack(t_data *data, int row, int col)
{
	int	newrow;
	int	newcol;
	int	i;
	int	*offset;

	data->visited[row][col] = 1;
	i = -1;
	offset = malloc(sizeof(int) * 4);
	offset[0] = 1;
	offset[1] = -1;
	offset[2] = 0;
	offset[3] = 0;
	while (++i < 4)
	{
		newcol = col + offset[i];
		newrow = row + offset[3 - i];
		if (data->map[newrow][newcol])
		{
			if (data->map[newrow][newcol] == '0'
				&& data->visited[newrow][newcol] == 0)
				if (backtrack(data, newrow, newcol))
					return (free(offset), 1);
		}
		else
			return (free(offset), 1);
	}
	return (free(offset), 0);
}

int	check_closed_walls(t_data *data)
{
	int	startrow;
	int	startcol;
	int	i;
	int	j;

	i = -1;
	startrow = -1;
	startcol = -1;
	while (++i < data->height)
	{
		j = 0;
		while (j < ft_strlen(data->map[i]))
		{
			if (data->map[i][j] == '0')
			{
				startrow = i;
				startcol = j;
				break ;
			}
			j++;
		}
		if (startrow != -1 && startcol != -1)
			break ;
	}
	if (backtrack(data, startrow, startcol))
		return (-1);
}

int	check_map(t_data *data)
{
	if (check_player_position(data) || check_closed_walls(data))
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
