/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:25:05 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/24 15:38:25 by tmoragli         ###   ########.fr       */
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

void	change_player_pos(double t, t_data *d, t_pos dir, int speed)
{
	double	v_x;
	double	v_y;
	int		mx;
	int		my;

	v_x = cos(t);
	v_y = sin(t);
	d->player.x = (int)d->convert.x / SIZE;
	d->player.y = (int)d->convert.y / SIZE;
	mx = (int)(d->convert.x + v_x * speed * (dir.x * 2)) / SIZE;
	my = (int)(d->convert.y + v_y * speed * (dir.y * 2)) / SIZE;
	if (d->player.x != mx && d->player.y != my)
	{
		if (d->map[my].line[(int)d->player.x] == '1'
			|| d->map[my].line[(int)d->player.x] == ' ')
			v_y = 0;
		if (d->map[(int)d->player.y].line[mx] == '1'
			|| d->map[(int)d->player.y].line[mx] == ' ')
			v_x = 0;
	}
	if (my < d->m_info->size.y && my >= 0 && mx < d->map[my].len
		&& mx >= 0 && d->map[my].line[mx] != '1')
		increment_pos(d, (v_x * speed) * (dir.x * 2),
			(v_y * speed) * (dir.y * 2));
}

int	move_player(int keycode, t_data *data)
{
	int	s;

	s = MOVE_SPEED;
	if (data->keys.shift)
		s += 1;
	if (keycode == XK_Escape)
	{
		ft_printf("You pressed escape key\nGame closed\n");
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
		change_player_pos(change_angle(get_rad(data->player.o), 90, '-'),
			data, point(1, 1, 0), s);
	if (keycode == XK_D)
		change_player_pos(change_angle(get_rad(data->player.o), 90, '-'),
			data, point(-1, -1, 0), s);
	return (0);
}
