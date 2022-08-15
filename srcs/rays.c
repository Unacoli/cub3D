/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/16 00:05:30 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	send_rays(t_data *data, t_pos start_point, int nb_rays)
{
	int		dof;
	double	atang;
	int		mx;
	int		my;

	data->ray.angle = get_rad(data->player.o);
	while (nb_rays > 0)
	{
		dof = 0;
		atang = -1 / tan(data->ray.angle);
		if (data->ray.angle > PI)
		{
			data->ray.y = (((int)start_point.y / 64) * 64) - 0.0001;
			data->ray.x = (start_point.y - data->ray.y) * atang + start_point.x;
			data->ray.y_dir = -64;
			data->ray.x_dir = (-data->ray.y_dir) *atang;
		}
		if (data->ray.angle < PI)
		{
			data->ray.y = (((int)start_point.y / 64) * 64) + 64;
			data->ray.x = (start_point.y - data->ray.y) * atang + start_point.x;
			data->ray.y_dir = 64;
			data->ray.x_dir = (-data->ray.y_dir) *atang;
		}
		if (data->ray.angle == 0 || data->ray.angle == PI)
		{
			data->ray.x = start_point.x;
			data->ray.y = start_point.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(data->ray.x / 64);
			my = (int)(data->ray.y / 64);
			if (mx < data->m_info->size.x && my < data->m_info->size.y && mx >= 0 && my >= 0
				&& data->map[my][mx] == '1')
				dof = 8;
			else
			{
				data->ray.x += data->ray.x_dir;
				data->ray.y += data->ray.y_dir;
				dof++;
			}
		}
		draw_ray(data, start_point, point(mx * 64, my * 64, 0));
		nb_rays--;
	}
}

void	draw_ray(t_data *data, t_pos start_point, t_pos end_point)
{
	double	t;
	int		length;

	t = get_rad(data->player.o);
	data->ray.x_dir = cos(t);
	data->ray.y_dir = sin(t);
	length = 0;
	(void)end_point;
	while (length < 600)
	{
		draw_pixel(data, start_point.x + data->ray.x_dir * length, start_point.y + data->ray.y_dir * length, data->white);
		length++;
	}
}
