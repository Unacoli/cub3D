/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 00:30:45 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/12 16:49:51 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_elem(char **map, int x, int y, int map_size)
{
	if (map[y][x] != '1' && map[y][x] != '0'
	&& map[y][x] != ' ' && is_player(map[y][x]))
		return (ft_printf("Error\nNot a valid map element: %c\n", map[y][x]));
	
	if (((map[y][x] == '0' || !is_player(map[y][x])) && is_border(map, x, y, map_size))
	|| (((map[y][x] == '0' || !is_player(map[y][x])) && is_opened(map, x, y, map_size))))
		return (ft_printf("Error\nMap is not closed at line: %d column: %d\n",
				y, x));
	return (0);
}

int	is_border(char **map, int x, int y, int map_size)
{
	if (y == 0 || y == map_size || x == 0 || x == (int)ft_strlen(map[y]))
		return (1);
	return (0);
}

int	is_valid_map(t_data *data, t_list *map)
{
	int	map_size;

	map_size = ft_lstsize(map);
	data->map = malloc(sizeof(char *) * (map_size + 1));
	if (!data->map)
		return (-1);
	data->map[map_size] = NULL;
	fill_map_array(data, map);
	if (scan_map(data->map, data))
		return (1);
	return (0);
}

int	is_valid_file(t_data *data)
{
	t_list	*file;
	t_list	*map;

	file = data->m_info->map;
	map = is_valid_id(file, data);
	if (!map)
		return (ft_printf("Error\nNo map given\n"));
	trim_textures(data);
	if (is_valid_map(data, map))
		return (1);
	return (0);
}

int	is_opened(char	**map, int x, int y, int map_size)
{
	if (x != 0)
		if (map[y][x - 1] != '0' && map[y][x - 1] != '1'
			&& is_player(map[y][x - 1]))
			return (1);
	if (x != (int)ft_strlen(map[y]))
		if (map[y][x + 1] != '0' && map[y][x + 1] != '1'
			&& is_player(map[y][x + 1]))
			return (1);
	if (y != map_size)
		if (map[y + 1][x] != '0' && map[y + 1][x] != '1'
			&& is_player(map[y + 1][x]))
			return (1);
	if (y != 0)
		if (map[y - 1][x] != '0' && map[y - 1][x] != '1'
			&& is_player(map[y - 1][x]))
			return (1);
	return (0);
}
