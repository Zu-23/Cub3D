/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhaddoum <zhaddoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:29:00 by alemsafi          #+#    #+#             */
/*   Updated: 2023/08/07 14:39:35 by zhaddoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\r' || c == '\t' || c == '\v')
		return (1);
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
		if (data->map[newrow][newcol] && data->map[newrow][newcol] != ' ')
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
