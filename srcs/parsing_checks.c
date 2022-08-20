/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:49:05 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/20 14:08:22 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (1);
	return (0);
}

int	is_border(t_line *map, int x, int y, int map_size)
{
	if (y == 0 || y == map_size || x == 0 || x == map[y].len)
		return (1);
	return (0);
}

double	find_long_line(t_line *map, t_data *data)
{
	int		i;
	double	len;

	i = 0;
	len = 0;
	while (i < data->m_info->size.y)
	{
		if (map->len > len)
			len = map->len;
		i++;
	}
	printf("%f\n", len);
	return (len);
}

int	is_valid_map(t_data *data, t_list *map)
{
	data->m_info->size.y = ft_lstsize(map);
	data->map = malloc(sizeof(t_line) * (data->m_info->size.y));
	if (!data->map)
		return (-1);
	fill_map_array(data, map);
	data->m_info->size.x = find_long_line(data->map, data);
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

int	is_opened(t_line *map, int x, int y, int map_size)
{
	if (x != 0)
		if (map[y].line[x - 1] != '0' && map[y].line[x - 1] != '1'
			&& is_player(map[y].line[x - 1]))
			return (1);
	if (x != map[y].len)
		if (map[y].line[x + 1] != '0' && map[y].line[x + 1] != '1'
			&& is_player(map[y].line[x + 1]))
			return (1);
	if (y != map_size)
		if (map[y + 1].line[x] != '0' && map[y + 1].line[x] != '1'
			&& is_player(map[y + 1].line[x]))
			return (1);
	if (y != 0)
		if (map[y - 1].line[x] != '0' && map[y - 1].line[x] != '1'
			&& is_player(map[y - 1].line[x]))
			return (1);
	return (0);
}
