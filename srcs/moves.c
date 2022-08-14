/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:25:05 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/14 18:05:34 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int keycode, t_data *data)
{
	double t;
	if (keycode == LEFT_ARR)
	{
		if (data->player.o + 5 > 360)
			data->player.o = -5;
		data->player.o += 5;
	}
	if (keycode == RIGHT_ARR)
	{
		if (data->player.o - 5 < 0)
			data->player.o = 365;
		data->player.o -= 5;
	}
	if (keycode == Z)
	{
		t = get_rad(data->player.o);
		data->direction.x = cos(t);
		data->direction.y = sin(t);
		data->player.x += data->direction.x * 0.1;
		data->player.y += data->direction.y * 0.1;
	}
	if (keycode == S)
	{
		t = get_rad(data->player.o);
		data->direction.x = cos(t);
		data->direction.y = sin(t);
		data->player.x -= data->direction.x * 0.1;
		data->player.y -= data->direction.y * 0.1;
	}
}

int	act_keypress(t_data *data)
{
	if (data->keys.l_arr)
		move_player(LEFT_ARR, data);
	if (data->keys.r_arr)
		move_player(RIGHT_ARR, data);
	if (data->keys.z)
		move_player(Z, data);
	if (data->keys.s)
		move_player(S, data);
	map_fill(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	hook_keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		printf("You pressed escape key\nGame closed\n");
		mlx_loop_end(data->mlx);
		return (0);
	}
	if (keycode == Z)
		data->keys.z = !data->keys.z;
	if (keycode == S)
		data->keys.s = !data->keys.s;
	if (keycode == LEFT_ARR)
		data->keys.l_arr = !data->keys.l_arr;
	if (keycode == RIGHT_ARR)
		data->keys.r_arr = !data->keys.r_arr;
	return (0);
}
