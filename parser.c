/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:27:34 by zhaddoum          #+#    #+#             */
/*   Updated: 2023/07/25 20:18:24 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	parse_map(char *line, t_data *data, char *content)
{
	char	*str;
	t_var	var;
	int		len;

	(void)content;
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
	free(str);
	return (0);
}

int	evaluate_parse_functions(char *line, t_data *data)
{
	int	success;
	int	i;

	success = 0;
	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
		|| line[i] == '\v' || line[i] == '\f')
		i++;
	if (line[i] == '\n')
		return (0);
	if (parse_texture(line, data, &success))
		return (-1);
	if (success == 1)
		return (0);
	if (parse_color(line, data, &success))
		return (-1);
	if (success == 1)
		return (0);
	if (parse_map(line, data, "01ESNW "))
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

int	backtrack(t_data *data, int row, int col)
{
	int	newrow;
	int	newcol;
	int	i;
	int	*offset;

	data->visited[row][col] = 1;
	i = -1;
	offset = (int [4]){0, 0, 1, -1};
	while (++i < 4)
	{
		newcol = col + offset[i];
		newrow = row + offset[3 - i];
		if (data->map[newrow][newcol])
		{
			if (data->map[newrow][newcol] == '0'
				&& data->visited[newrow][newcol] == 0)
				if (newrow == 0 || backtrack(data, newrow, newcol))
					return (1);
		}
		else
			return (1);
	}
	return (0);
}
