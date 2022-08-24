/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:56:07 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/24 16:23:57 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cub(t_data *data, double ray_angle, int rays)
{
	double	player_angle;

	player_angle = get_rad(data->player.o);
	data->ray->angle_diff = change_rad_angle(player_angle, ray_angle, '-');
	data->ray_length = data->ray_length * cos(data->ray->angle_diff);
	data->ray->line_height = (SIZE_3D * HEIGHT_3D) / data->ray_length;
	data->ray->ty_step = data->text[data->ray->wall].size.y
		/ data->ray->line_height;
	data->ray->ty_offset = 0;
	if (data->ray->line_height > HEIGHT_3D)
	{
		data->ray->ty_offset = (data->ray->line_height - HEIGHT_3D) / 2;
		data->ray->line_height = HEIGHT_3D;
	}
	data->ray->line_offset = (HEIGHT_3D - data->ray->line_height) / 2;
	draw_line(data, rays, &(data->text[data->ray->wall]), data->ray);
}

void	h_ray_set(t_data *data, double ray_angle)
{
	data->ray->wall_color = data->c_palette->red;
	data->ray->ray_pos = point(data->ray->h_ray.x,
			data->ray->h_ray.y, 0);
	data->ray_length = data->ray->h_ray.length;
	data->ray->tx = (((int)data->ray->ray_pos.x % SIZE_3D));
	if (ray_angle > PI)
		set_wall(data, 0);
	if (ray_angle < PI)
		set_wall(data, 1);
}

void	v_ray_set(t_data *data, double ray_angle)
{
	data->ray->wall_color = data->c_palette->blue;
	data->ray->ray_pos = point(data->ray->v_ray.x,
			data->ray->v_ray.y, 0);
	if (ray_angle < (PI / 2) || ray_angle > ((3 * PI) / 2))
		set_wall(data, 3);
	if (ray_angle > (PI / 2) && ray_angle < ((3 * PI) / 2))
		set_wall(data, 2);
	data->ray_length = data->ray->v_ray.length;
	data->ray->tx = ((int)data->ray->ray_pos.y % SIZE_3D);
}

void	raycasting(t_data *data, t_pos start, int nb_rays)
{
	double	ray_angle;
	int		rays;

	ray_angle = get_rad(change_angle(data->player.o, FOV / 2, '-'));
	rays = 1;
	while (rays <= nb_rays)
	{
		cast_h_ray(data, start, ray_angle);
		cast_v_ray(data, start, ray_angle);
		if (data->ray->h_ray.length < data->ray->v_ray.length)
			h_ray_set(data, ray_angle);
		else
			v_ray_set(data, ray_angle);
		draw_cub(data, ray_angle, rays);
		ray_angle = change_rad_angle(ray_angle, RAD_1 / (NB_RAYS / FOV), '+');
		rays++;
	}
}
