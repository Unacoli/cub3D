/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:49:05 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/27 21:56:01 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_border(t_data *data, int x, int y, int map_size)
{
	if (y == 0 || y == map_size || x == 0 || x == data->map[y].len)
		return (1);
	if (!is_inmap(data, x, y + 1) || !is_inmap(data, x, y - 1))
		return (1);
	return (0);
}

int	is_valid_map(t_data *data, t_list *map)
{
	data->m_info->size.y = ft_lstsize(map) + 1;
	data->map = malloc(sizeof(t_line) * (data->m_info->size.y));
	if (!data->map)
		return (1);
	if (fill_map_array(data, map))
		return (1);
	if (scan_map(data->map, data, 0, 0))
		return (1);
	return (0);
}

int	is_valid_file(t_data *data)
{
	t_list	*file;
	t_list	*map;

	file = data->m_info->map;
	map = is_valid_id(file, data, 0);
	if (!map)
		return (printf("No map given\n"));
	if (trim_textures(data))
		return (1);
	if (is_valid_map(data, map))
		return (1);
	return (0);
}

int	is_opened(t_data *data, int x, int y)
{
	if (is_inmap(data, x - 1, y) && data->map[y].line
		&& data->map[y].line[x - 1] != '0'
		&& data->map[y].line[x - 1] != '1'
		&& is_player(data->map[y].line[x - 1]))
		return (1);
	if (is_inmap(data, x + 1, y) && data->map[y].line
		&& data->map[y].line[x + 1] != '0'
		&& data->map[y].line[x + 1] != '1'
		&& is_player(data->map[y].line[x + 1]))
		return (1);
	if (is_inmap(data, x, y + 1) && data->map[y + 1].line
		&& data->map[y + 1].line[x] != '0'
		&& data->map[y + 1].line[x] != '1'
		&& is_player(data->map[y + 1].line[x]))
		return (1);
	if (is_inmap(data, x, y - 1) && data->map[y - 1].line
		&& data->map[y - 1].line[x] != '0'
		&& data->map[y - 1].line[x] != '1'
		&& is_player(data->map[y - 1].line[x]))
		return (1);
	return (0);
}
