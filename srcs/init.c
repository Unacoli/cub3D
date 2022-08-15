/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:23:04 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/15 15:02:10 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_window_size(t_data *data)
{
	data->w_height = data->m_info->size.y * SIZE;
	data->w_width = data->m_info->size.x * SIZE;
}

void	init_mlx_data(t_data *data, int trash)
{
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &data->s_width, &data->s_height);
	setup_window_size(data);
	data->win = mlx_new_window(data->mlx, data->w_width, data->w_height,
				"The room");
	data->img = mlx_new_image(data->mlx, data->w_width, data->w_height);
	data->addr = mlx_get_data_addr(data->img, &trash, &trash, &trash);
	data->draw = (t_color *)data->addr;
}

void	start_game(t_data *data)
{
	init_mlx_data(data, 0);
	if (data->player.facing == 'N')
		data->player.o = 90;
	if (data->player.facing == 'E')
		data->player.o = 180;
	if (data->player.facing == 'S')
		data->player.o = 270;
	if (data->player.facing == 'W')
		data->player.o = 360;
	map_fill(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_hook(data->win, 33, 1L << 17, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1L << 0, hook_keypress, data);
    mlx_hook(data->win, 3, 1L << 1, hook_keypress, data);
	mlx_loop_hook(data->mlx, &act_keypress, data);
	mlx_loop(data->mlx);
}

void	init_subdata(t_data *data)
{
	ft_memset(data->m_info, 0, sizeof(t_map));
	data->player_color = get_rgb(255, 0, 0, 1);
	data->white = get_rgb(255, 255, 255, 1);
}

void	init_game_data(t_data *data, char **av)
{
	ft_memset(data, 0, sizeof(t_data));
	if (allocate_game_data(data, av))
		exit_game(data, "Failed allocation, exiting\n");
	init_subdata(data);
}
