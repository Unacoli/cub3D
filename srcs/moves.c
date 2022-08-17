/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:25:05 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/18 00:28:13 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(int way, t_data *data)
{
	if (way == RIGHT_ARR)
	{
		if (data->player.o + 5 > 360)
			data->player.o = -5;
		data->player.o += 5;
	}
	if (way == LEFT_ARR)
	{
		if (data->player.o - 5 < 0)
			data->player.o = 365;
		data->player.o -= 5;
	}
}

void	change_player_pos(double orientation, t_data *data, t_pos dir)
{
	double	t;
	double	v_x;
	double	v_y;

	t = get_rad(orientation);
	v_x = cos(t);
	v_y = sin(t);
	if (data->map[(int)(data->player.y + (v_y * 0.1) * dir.y)][(int)(data->player.x + (v_x * 0.1) * dir.x)] != '1')
	{
		data->player.x += (v_x * 0.1) * dir.x;
		data->player.y += (v_y * 0.1) * dir.y;
	}
}

void	move_player(int keycode, t_data *data)
{
	if (keycode == LEFT_ARR || keycode == RIGHT_ARR)
		rotate_player(keycode, data);
	if (keycode == Z || keycode == W)
		change_player_pos(data->player.o, data, point(1, 1, 0));
	if (keycode == S)
		change_player_pos(data->player.o, data, point(-1, -1, 0));
	if (keycode == Q)
		change_player_pos(change_angle(data->player.o, 90, '-'), data, point(1, 1, 0));
	if (keycode == D)
		change_player_pos(change_angle(data->player.o, 90, '-'), data, point(-1, -1, 0));
	
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
	if (data->keys.q)
		move_player(Q, data);
	if (data->keys.d)
		move_player(D, data);
	map_fill(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	hook_keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		ft_printf("You pressed escape key\nGame closed\n");
		mlx_loop_end(data->mlx);
		return (0);
	}
	if (keycode == Z || keycode == W)
		data->keys.z = !data->keys.z;
	if (keycode == S)
		data->keys.s = !data->keys.s;
	if (keycode == Q || keycode == A)
		data->keys.q = !data->keys.q;
	if (keycode == D)
		data->keys.d = !data->keys.d;
	if (keycode == LEFT_ARR)
		data->keys.l_arr = !data->keys.l_arr;
	if (keycode == RIGHT_ARR)
		data->keys.r_arr = !data->keys.r_arr;
	return (0);
}
