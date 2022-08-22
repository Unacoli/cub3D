/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:38:14 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/22 22:38:18 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_data(t_data *data, t_line *map)
{
	int	i;

	i = 0;
	while (i < data->m_info->size.y)
	{
		free(map[i].line);
		i++;
	}
	free(map);
}

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	free(data->m_info->ea_path);
	free(data->m_info->no_path);
	free(data->m_info->we_path);
	free(data->m_info->so_path);
	free(data->m_info);
	free(data->map_path);
	while (i < 4)
	{
		if (data->text[i].img)
			mlx_destroy_image(data->mlx, data->text[i].img);
		i++;
	}
	free(data->text);
}

void	free_game_data(t_data *data)
{
	free_map_data(data, data->map);
	free_textures(data);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
}

void	exit_game(t_data *data, char *msg)
{
	ft_printf("%s\n", msg);
	free_game_data(data);
	exit(1);
}
