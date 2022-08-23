/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:25:05 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/23 02:01:21 by tmoragli         ###   ########.fr       */
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

void	change_player_pos(double orientation, t_data *data, t_pos dir, int speed)
{
	double	t;
	double	v_x;
	double	v_y;
	int		mx;
	int		my;

	t = get_rad(orientation);
	v_x = cos(t);
	v_y = sin(t);
	mx = (int)(data->convert.x + v_x * speed * (dir.x * 4)) / 64;
	my = (int)(data->convert.y + v_y * speed * (dir.y * 4)) / 64;
	if (my < data->m_info->size.y && my >= 0
			&& mx < data->map[my].len
			&& mx >= 0
			&& data->map[my].line[mx] != '1')
	{
		data->convert.x += (v_x * speed) * (dir.x * 2);
		data->convert.y += (v_y * speed) * (dir.y * 2);
	}
}

int	move_player(int keycode, t_data *data)
{
	int speed;

	speed = MOVE_SPEED;
	if (data->keys.shift)
		speed += 1;
	if (keycode == XK_Escape)
	{
		ft_printf("You pressed escape key\nGame closed\n");
		mlx_loop_end(data->mlx);
		return (0);
	}
	if (keycode == XK_Left || keycode == XK_Right)
		rotate_player(keycode, data, ROTATE_SPEED);
	if (keycode == XK_W)
		change_player_pos(data->player.o, data, point(1, 1, 0), speed);
	if (keycode == XK_S)
		change_player_pos(data->player.o, data, point(-1, -1, 0), speed);
	if (keycode == XK_A)
	{
		change_player_pos(change_angle(data->player.o, 90, '-'),
			data, point(1, 1, 0), speed);
	}
	if (keycode == XK_D)
	{
		change_player_pos(change_angle(data->player.o, 90, '-'),
			data, point(-1, -1, 0), speed);
	}
	return (0);
}
