/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:43:47 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/20 14:42:23 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_map_width(char **map)
{
	int	i;
	int	row_len;

	row_len = 0;
	i = 0;
	while (map && map[i])
	{
		if ((int)ft_strlen(map[i]) > row_len)
			row_len = ft_strlen(map[i]);
		i++;
	}
	return (row_len);
}

void	fill_map_array(t_data *data, t_list *map)
{
	int		i;
	char	*line;

	i = 0;
	while (map)
	{
		line = (char *)(map->content);
		data->map[i].line = ft_strdup(line);
		data->map[i].len = ft_strlen(line);
		i++;
		map = map->next;
	}
}
