/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:23:04 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/19 13:36:13 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_window_size(t_data *data)
{
	data->w_height = data->m_info->size.y * SIZE;
	data->w_width = data->m_info->size.x * SIZE;
}

void	init_mlx_data(t_data *data, int trash)
{
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &data->s_width, &data->s_height);
	setup_window_size(data);
	data->win = mlx_new_window(data->mlx, data->w_width,
			data->w_height, "cub3D");
	data->img_2d = mlx_new_image(data->mlx, data->w_width, data->w_height);
	data->img_3d = mlx_new_image(data->mlx, 320, 160);
	data->addr_2d = mlx_get_data_addr(data->img_2d, &trash, &trash, &trash);
	data->addr_3d = mlx_get_data_addr(data->img_3d, &trash, &trash, &trash);
	data->draw_2d = (t_color *)data->addr_2d;
	data->draw_3d = (t_color *)data->addr_3d;
}

void	init_subdata(t_data *data)
{
	ft_memset(data->m_info, 0, sizeof(t_map));
	data->red = get_rgb(255, 0, 0, 1);
	data->white = get_rgb(255, 255, 255, 1);
	data->black = get_rgb(0, 0, 0, 0);
	data->blue = get_rgb(30, 144, 255, 0);
}

void	init_game_data(t_data *data, char **av)
{
	ft_memset(data, 0, sizeof(t_data));
	if (allocate_game_data(data, av))
		exit_game(data, "Failed allocation, exiting\n");
	init_subdata(data);
}
