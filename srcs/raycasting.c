/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:56:07 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/19 15:20:05 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_data *data, t_pos start, int nb_rays)
{
	double	ray_angle;
	double	player_angle;
	int		rays;

	ray_angle = get_rad(change_angle(data->player.o, 30, '-'));
	rays = 0;
	player_angle = get_rad(data->player.o);
	while (rays < nb_rays)
	{
		cast_h_ray(data, start, ray_angle);
		cast_v_ray(data, start, ray_angle);
		if (data->h_ray.length < data->v_ray.length)
		{
			draw_ray(data, start, &data->h_ray, ray_angle);
			data->ray_length = data->h_ray.length;
			data->wall_color = data->red;
		}
		else
		{
			draw_ray(data, start, &data->v_ray, ray_angle);
			data->ray_length = data->v_ray.length;
			data->wall_color = data->blue;
		}
		data->ray_ratio = 8 * (nb_rays / FOV);
		data->angle_diff = change_rad_angle(player_angle, ray_angle, '-');
		data->ray_length = data->ray_length * cos(data->angle_diff);
		data->line_height = 320 * 64 / data->ray_length;
		if (data->line_height > 320)
			data->line_height = 320;
		data->line_offset = 160 - data->line_height / 2;
		draw_line(data, rays);
		ray_angle = change_rad_angle(ray_angle, RAD_1, '+');
		rays++;
	}
}
