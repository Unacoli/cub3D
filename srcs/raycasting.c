/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:56:07 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/23 02:52:46 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_data *data, t_pos start, int nb_rays)
{
	double	ray_angle;
	double	player_angle;
	int		rays;

	ray_angle = get_rad(change_angle(data->player.o, FOV / 2, '-'));
	rays = 1;
	player_angle = get_rad(data->player.o);
	while (rays <= nb_rays)
	{
		cast_h_ray(data, start, ray_angle);
		cast_v_ray(data, start, ray_angle);
		if (data->ray->h_ray.length < data->ray->v_ray.length)
		{
			data->ray->wall_color = data->c_palette->red;
			draw_ray(data, start, &data->ray->h_ray, ray_angle);
			data->ray->ray_pos = point(data->ray->h_ray.x, data->ray->h_ray.y, 0);
			data->ray_length = data->ray->h_ray.length;
			if (ray_angle > PI)
				set_wall(data, 0);
			if (ray_angle < PI)
				set_wall(data, 1);
			data->ray->tx = ((int)data->ray->ray_pos.x % 64);
		}
		else
		{
			data->ray->wall_color = data->c_palette->blue;
			draw_ray(data, start, &data->ray->v_ray, ray_angle);
			data->ray->ray_pos = point(data->ray->v_ray.x, data->ray->v_ray.y, 0);
			if (ray_angle < P2 || ray_angle > P3)
				set_wall(data, 2);
			if (ray_angle > P2 && ray_angle < P3)
				set_wall(data, 3);
			data->ray_length = data->ray->v_ray.length;
			data->ray->tx = ((int)data->ray->ray_pos.y % 64);
		}
		data->ray->angle_diff = change_rad_angle(player_angle, ray_angle, '-');
		data->ray_length = data->ray_length * cos(data->ray->angle_diff);
		data->ray->line_height = (SIZE * HEIGHT_3D) / data->ray_length;
		data->ray->ty_step = data->text[data->ray->wall].size.y / data->ray->line_height;
		data->ray->ty_offset = 0;
		if (data->ray->line_height > HEIGHT_3D)
		{
			data->ray->ty_offset = (data->ray->line_height - HEIGHT_3D) / 2;
			data->ray->line_height = HEIGHT_3D;
		}
		data->ray->line_offset = (HEIGHT_3D - data->ray->line_height) / 2;
		draw_line(data, rays, &(data->text[data->ray->wall]), data->ray);
		ray_angle = change_rad_angle(ray_angle, RAD_1 / (NB_RAYS / FOV), '+');
		rays++;
	}
}
