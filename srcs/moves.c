/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:25:05 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/27 19:29:20 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(int way, t_data *data, int speed)
{
	if (way == XK_Right)
	{
		if (data->player.o + speed > 360)
			data->player.o = -speed;
		data->player.o += speed;
	}
	if (way == XK_Left)
	{
		if (data->player.o - speed < 0)
			data->player.o = 360 + speed;
		data->player.o -= speed;
	}
}

void	increment_pos(t_data *data, double x, double y)
{
	data->convert.x += x;
	data->convert.y += y;
	data->p_3d = point_3d(data->convert.x, data->convert.y);
}

int	move_player(int keycode, t_data *data)
{
	int	s;

	s = MOVE_SPEED;
	if (data->keys.shift)
		s += 2;
	if (keycode == XK_Escape)
	{
		printf("You pressed escape key\nGame closed\n");
		mlx_loop_end(data->mlx);
		return (0);
	}
	if (keycode == XK_Left || keycode == XK_Right)
		rotate_player(keycode, data, ROTATE_SPEED);
	if (keycode == XK_W)
		change_player_pos(get_rad(data->player.o), data, point(1, 1, 0), s);
	if (keycode == XK_S)
		change_player_pos(get_rad(data->player.o), data, point(-1, -1, 0), s);
	if (keycode == XK_A)
		change_player_pos(get_rad(change_angle(data->player.o, 90, '-')),
			data, point(1, 1, 0), s);
	if (keycode == XK_D)
		change_player_pos(get_rad(change_angle(data->player.o, 90, '-')),
			data, point(-1, -1, 0), s);
	return (0);
}
