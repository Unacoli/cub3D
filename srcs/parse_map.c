/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 00:35:46 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/19 13:42:06 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_elem(char **map, int x, int y, int map_size)
{
	if (map[y][x] != '1' && map[y][x] != '0'
	&& map[y][x] != ' ' && is_player(map[y][x]))
		return (ft_printf("Error\nNot a valid map element: %c\n", map[y][x]));
	if (((map[y][x] == '0' || !is_player(map[y][x]))
		&& is_border(map, x, y, map_size)) || (((map[y][x] == '0'
		|| !is_player(map[y][x])) && is_opened(map, x, y, map_size))))
		return (ft_printf("Error\nMap is not closed at line: %d column: %d\n",
				y, x));
	return (0);
}

int	scan_map(char **map, t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map && map[y][x])
		{
			if (!is_player(map[y][x]))
			{
				data->player = point(x, y, map[y][x]);
				data->nb_player++;
			}
			if (data->nb_player > 1)
				return (ft_printf("Error\nToo many player elements\n"));
			if (check_elem(map, x, y, str_arr_size(map)))
				return (1);
			x++;
		}
		y++;
	}
	if (data->nb_player < 1)
		return (ft_printf("Error\nNo player on map, (N, S, W, E)\n"));
	return (0);
}

int	parse_map(t_data *data, int fd)
{
	int		ret;
	char	*line;

	ret = 0;
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
		return (ft_error("No map given, couldn't open file"));
	while (get_next_line(fd, &line))
	{
		if (!only_isspace(line))
		{
			ft_lstadd_back(&(data->m_info->map), ft_lstnew(line));
			ft_printf("%s\n", line);
		}
		else
			free(line);
	}
	ft_lstadd_back(&(data->m_info->map), ft_lstnew(line));
	ft_printf("%s\n", line);
	if (is_valid_file(data))
		ret++;
	ft_lstclear(&data->m_info->map, &free);
	return (ret);
}
