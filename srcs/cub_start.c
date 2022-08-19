/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:37:36 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/19 15:17:39 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_hook(data->win, DestroyNotify, 1L << 17, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1L << 0, hook_keypress, data);
	mlx_hook(data->win, 3, 1L << 1, hook_keypress, data);
	mlx_loop_hook(data->mlx, &act_keypress, data);
	mlx_loop(data->mlx);
}

int	cub_start(t_data *data)
{
	if (parse_map(data, 0))
		return (ft_error("File error, check description above"));
	else
		start_game(data);
	return (0);
}
