/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:43:47 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/27 19:29:34 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_map_array(t_data *data, t_list *map)
{
	int		i;
	char	*line;

	i = 0;
	data->map[i].line = ft_strdup("\0");
	if (!data->map[i].line)
		exit_game(data, "Allocation failed", 0);
	data->map[i].len = (int)ft_strlen(data->map[i].line);
	i++;
	while (map && i <= data->m_info->size.y)
	{
		line = (char *)(map->content);
		data->map[i].line = ft_strdup(line);
		if (!data->map[i].line)
			exit_game(data, "Allocation failed", 0);
		data->map[i].line = swap_str(data->map[i].line,
				ft_strjoin(" ", data->map[i].line));
		data->map[i].len = ft_strlen(line);
		i++;
		map = map->next;
	}
}
