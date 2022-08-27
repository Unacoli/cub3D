/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:38:14 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/27 22:02:56 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_data(t_line *map, int size)
{
	int	i;

	i = 0;
	while (map && i < size && map[i].line)
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
	if (data->map)
		free_map_data(data->map, data->m_info->size.y);
	if (data->c_palette)
		free(data->c_palette);
	if (data->ray)
		free(data->ray);
	if (data->player_ray)
		free(data->player_ray);
	if (data->m_info)
		free_textures(data, status);
	if (data->screen && data->screen->img)
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
	printf("%s\n", msg);
	free_game_data(data, status);
	exit(status);
}
