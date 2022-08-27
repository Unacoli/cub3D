/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nargouse <nargouse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:45:43 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/27 21:15:28 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_game(t_data *data)
{
	init_mlx_data(data, 0);
	if (data->player.facing == 'N')
		data->player.o = 270;
	if (data->player.facing == 'E')
		data->player.o = 360;
	if (data->player.facing == 'S')
		data->player.o = 90;
	if (data->player.facing == 'W')
		data->player.o = 180;
	mlx_put_image_to_window(data->mlx, data->win, data->screen->img, 0, 0);
	mlx_hook(data->win, DestroyNotify, 1L << 17, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1L << 0, hook_keypress, data);
	mlx_hook(data->win, 3, 1L << 1, hook_keypress, data);
	mlx_loop_hook(data->mlx, &act_keypress, data);
	raycasting(data, point(data->p_3d.x, data->p_3d.y, 0), NB_RAYS);
	mlx_loop(data->mlx);
}
