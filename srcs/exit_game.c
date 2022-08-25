/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:38:14 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/25 03:33:10 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_data(t_data *data, t_line *map)
{
	int	i;

	i = 0;
	while (map && i < data->m_info->size.y)
	{
		free(map[i].line);
		i++;
	}
	free(map);
}

void	free_textures(t_data *data, int status)
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
		if (data->text[i].img && !status)
			mlx_destroy_image(data->mlx, data->text[i].img);
		i++;
	}
	free(data->text);
}

void	free_game_data(t_data *data, int status)
{
	free_map_data(data, data->map);
	free(data->c_palette);
	free(data->ray);
	free_textures(data, status);
	if (data->screen->img)
		mlx_destroy_image(data->mlx, data->screen->img);
	free(data->screen);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
}

void	exit_game(t_data *data, char *msg, int status)
{
	ft_printf("%s\n", msg);
	free_game_data(data, status);
	exit(status);
}
