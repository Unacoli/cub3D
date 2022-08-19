/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nargouse <nargouse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:38:14 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/19 12:38:36 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game_data(t_data *data)
{
	free(data->m_info->ea_path);
	free(data->m_info->no_path);
	free(data->m_info->we_path);
	free(data->m_info->so_path);
	free(data->m_info);
	str_arr_free(data->map);
	free(data->map_path);
	if (data->img_2d)
		mlx_destroy_image(data->mlx, data->img_2d);
	if (data->img_3d)
		mlx_destroy_image(data->mlx, data->img_3d);
	if (data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	free(data);
}

void	exit_game(t_data *data, char *msg)
{
	ft_printf("%s\n", msg);
	free_game_data(data);
	exit(1);
}