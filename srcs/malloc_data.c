/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:40:09 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/27 00:07:15 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_game_data(t_data *data, char **av)
{
	int	i;

	i = 0;
	data->m_info = (t_map *)malloc(sizeof(t_map));
	data->text = (t_text *)malloc(sizeof(t_text) * 4);
	data->c_palette = (t_color *)malloc(sizeof(t_color));
	data->screen = (t_text *)malloc(sizeof(t_text));
	data->ray = (t_draw *)malloc(sizeof(t_draw));
	data->player_ray = (t_draw *)malloc(sizeof(t_draw));
	data->map_path = ft_strdup(av[1]);
	if (!(data->ray && data->screen && data->c_palette && data->text
			&& data->m_info && data->map_path))
	{
		free(data->map_path);
		return (1);
	}	
	while (i < 4)
		data->text[i++].img = NULL;
	data->screen->img = NULL;
	return (0);
}
