/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_player_pos_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nargouse <nargouse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:42:35 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/27 21:14:31 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mx = (int)(d->convert.x + v_x * speed * (dir.x * 1.5)) / SIZE;
	my = (int)(d->convert.y + v_y * speed * (dir.y * 1.5)) / SIZE;
	if (d->player.x != mx && d->player.y != my)
	{
		if (d->map[my].line[(int)d->player.x] == '1'
			|| d->map[my].line[(int)d->player.x] == ' ')
			v_y = 0;
		if (d->map[(int)d->player.y].line[mx] == '1'
			|| d->map[(int)d->player.y].line[mx] == ' ')
			v_x = 0;
	}
	if (is_inmap(d, mx, my) && d->map[my].line[mx] != '1')
		increment_pos(d, (v_x * speed) * (dir.x),
			(v_y * speed) * (dir.y));
}
