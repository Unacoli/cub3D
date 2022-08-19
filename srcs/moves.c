/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:25:05 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/19 01:11:02 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(int way, t_data *data)
{
	if (way == XK_Right)
	{
		if (data->player.o + 5 > 360)
			data->player.o = -5;
		data->player.o += 5;
	}
	if (way == XK_Left)
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

int	move_player(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		ft_printf("You pressed escape key\nGame closed\n");
		mlx_loop_end(data->mlx);
		return (0);
	}
	if (keycode == XK_Left || keycode == XK_Right)
		rotate_player(keycode, data);
	if (keycode == XK_W)
		change_player_pos(data->player.o, data, point(1, 1, 0));
	if (keycode == XK_S)
		change_player_pos(data->player.o, data, point(-1, -1, 0));
	if (keycode == XK_A)
		change_player_pos(change_angle(data->player.o, 90, '-'), data, point(1, 1, 0));
	if (keycode == XK_D)
		change_player_pos(change_angle(data->player.o, 90, '-'), data, point(-1, -1, 0));
	return (0);
}
