#include "42-functions/LIBFT_42/libft.h"
#include "42-functions/Get_next_line_42/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
//delete later
#include<string.h>
#include<stdlib.h>

/*
DATA:
	1- DIRECTION TEXTURES: IT HAS 2 ARGUMENTS *ID AND *DESTINATION
	2- FLOOR COLOR: IT HAS 4 ARGUMENTS *ID *RED *GREEN *BLUE
	3- CEILING COLOR: IT HAS 4 ARGUMENTS *ID *RED *GREEN *BLUE
	4- MAP
*/
typedef struct s_texture
{
	char	id[3];
	char	dest[200];
}t_texture;

typedef struct s_color
{
	char	id[2];
	int		red;
	int		green;
	int		blue;
}t_color;

typedef struct s_data
{
	t_texture	no;
	t_texture	so;
	t_texture	ea;
	t_texture	we;
	t_color		f;
	t_color		c;
	// char		map[HEIGHT][WEIDTH]

}t_data;

int	ft_error(char *str)
{
	perror(str);
	exit(1);
}

int	ft_isspace(int c)
{
	return ((c == '\f') || (c == '\r') || (c == '\t') || (c == '\v'));
}

int	fill_texture(char *line, t_texture texture)
{
	char	*after_xpm;

	after_xpm = ft_strstr(line, ".xpm") + 4;
	while (after_xpm != (char *)4 && *after_xpm != '\n')
	{
		if (*after_xpm != ' ')
			return (-1);
		after_xpm++;
	}
	ft_strcpy(texture.id, ft_strtok(line, " "));
	ft_strcpy(texture.dest, ft_strtok(NULL, " \n"));
	printf("id: %s\ndest: %s\n", texture.id, texture.dest);
	if (texture.dest == NULL || ft_strstr(texture.dest, ".xpm") == NULL)
		return (-1);
	return (0);
}

int	check_rgb(char *rgb)
{
	int	i;

	i = 0;
	printf("RGB: %s\n", rgb);
	while (rgb[i])
	{
		//printf("rgb |%c|\n",rgb[i]);
		if (ft_isdigit(rgb[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	fill_color(char *line, t_color color)
{
	char	*rgb[3];
	int		i;

	i = 0;	
	ft_strcpy(color.id, ft_strtok(line, " "));
	while (i < 3)
	{
		rgb[i] = ft_strtok(NULL, " ,\n");
		if (check_rgb(rgb[i++]))
			return (-1);
	}
	color.red = ft_atoi(rgb[0]);
	color.green = ft_atoi(rgb[1]);
	color.blue = ft_atoi(rgb[2]);
	if ((color.red < 0 || color.red > 255)
		|| (color.green < 0 || color.green > 255)
		|| (color.blue < 0 || color.blue > 255))
		return (-1); 

	printf("id %s red %d green %d blue %d\n", color.id,color.red, color.green, color.blue);
	return (0);
}

int	parse_color(char *line, t_data *data)
{
	if (line[0] == 'C' && line[1] == ' ')
	{
		if (fill_color(line, data->c))
			return (-1);
	}
	else if (line[0] == 'F' && line[1] == ' ')
	{
		if (fill_color(line, data->f))
			return (-1);
	}
	return (0);
}

int	parse_texture(char *line, t_data *data)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		if (fill_texture(line, data->no))
			return (-1);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		if (fill_texture(line, data->so))
			return (-1);
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if (fill_texture(line, data->ea))
			return (-1);
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		if (fill_texture(line, data->we))
			return (-1);
	}
	return (0);
}

int	parse_map(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
}

int	evaluate_parse_functions(char *line, t_data *data)
{
	if (parse_texture(line, data))
		return (-1);
	if (parse_color(line, data))
		return (-1);
	if (parse_map(line, data))
		return (-1);
	return (0);
}

int	parse_file(int fd, t_data *data)
{
	int		error;
	char	*line;

	error = 0;
	line  = get_next_line(fd);
	if (line == NULL)
		ft_error("Error\nin file handling\n");
	while (line)
	{
		if (evaluate_parse_functions(line, data))
		{
			error = -2;
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (error)
		ft_error("Error\nin file parsing\n");
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		parse_file(fd, &data);
	}
	else
		ft_error("Error\nwrong number of arguments\n");
}


//plan for parsin the map
//1- we check if the line is valid (valid means it contains only 0 1 N,S,E,W)
//2- remove any spaces in the line
//3- save the line in the map element
//4- 