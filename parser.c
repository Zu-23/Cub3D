/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:27:34 by zhaddoum          #+#    #+#             */
/*   Updated: 2023/08/02 23:07:51 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	parse_map(char *line, t_data *data, int flag)
{
	char	*str;
	t_var	var;
	int		i;

	var = (t_var){0, 0, 0};
	i = 0;
	while (line[i] == ' ')
		i++;
	if ((!data->ea.id[0] || !data->no.id[0] || !data->so.id[0]
			|| !data->we.id[0] || !data->c.id[0] || !data->f.id[0])
		&& line[i] == '\n')
		return (0);
	if ((flag == 2 && line[i] == '\n') || check_valid_line(line, data))
		return (-1);
	str = malloc(ft_strlen(line) + 1);
	if (!str)
		return (-1);
	while (line[var.i] && line[var.i] != '\n')
	{
		while (line[var.i] == ' ' && var.i++)
			str[var.j++] = ' ';
		str[var.j++] = line[var.i++];
	}
	str[var.j] = '\0';
	return (ft_strcpy(data->map[data->height++], str), free(str), 0);
}

void	no_newline_for_map(t_data *data, int *flag, char *line)
{
	if (data->ea.id[0] && data->no.id[0] && data->so.id[0] && data->we.id[0]
		&& data->c.id[0] && data->f.id[0])
	{
		if (!*flag)
			(*flag)++;
		if (ft_strchr(line, '1') || ft_strchr(line, '0'))
			if (*flag == 1)
				(*flag)++;
	}
}

int	evaluate_parse_functions(char *line, t_data *data)
{
	int			success;
	int			i;
	static int	flag;

	success = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (parse_texture(line, data, &success))
		return (-1);
	if (success == 1)
		return (0);
	if (parse_color(line, data, &success))
		return (-1);
	if (success == 1)
		return (0);
	no_newline_for_map(data, &flag, line);
	if (parse_map(line, data, flag))
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
				&& data->map[var.j][var.i] != '1'
				&& data->map[var.j][var.i] != ' ')
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
