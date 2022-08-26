/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:56:07 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/27 00:23:35 by tmoragli         ###   ########.fr       */
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

void	h_ray_set(t_data *data, double ray_angle, t_draw *ray)
{
	ray->pos = point(ray->h_ray.x,
			ray->h_ray.y, 0);
	data->ray_length = ray->h_ray.length;
	ray->tx = (((int)ray->pos.x % 64));
	if (ray_angle > PI)
		set_wall(data, 0);
	if (ray_angle < PI)
		set_wall(data, 1);
}

void	v_ray_set(t_data *data, double ray_angle, t_draw *ray)
{
	ray->pos = point(ray->v_ray.x,
			ray->v_ray.y, 0);
	if (ray_angle < (PI / 2) || ray_angle > ((3 * PI) / 2))
		set_wall(data, 2);
	if (ray_angle > (PI / 2) && ray_angle < ((3 * PI) / 2))
		set_wall(data, 3);
	data->ray_length = ray->v_ray.length;
	ray->tx = ((int)ray->pos.y % 64);
}

void	send_player_ray(t_data *data, t_pos start)
{
	cast_h_ray(data, start, data->player_ray->angle, data->player_ray);
	cast_v_ray(data, start, data->player_ray->angle, data->player_ray);
	if (data->player_ray->h_ray.length < data->player_ray->v_ray.length)
		h_ray_set(data, data->player_ray->angle, data->player_ray);
	else
		v_ray_set(data, data->player_ray->angle, data->player_ray);
	data->player_ray->adj = 1000;
}

void	raycasting(t_data *data, t_pos start, int nb_rays)
{
	double	ray_angle;
	int		rays;

	rays = 0;
	data->player_ray->angle = get_rad(data->player.o);
	send_player_ray(data, start);
	while (rays < nb_rays)
	{
		ray_angle = atan((rays - (WIDTH_3D / 2)) / data->player_ray->adj);
		if (ray_angle > PI * 2)
				ray_angle -= (PI * 2);
		if (ray_angle < 0)
			ray_angle += (PI * 2);
		ray_angle = change_rad_angle(data->player_ray->angle, ray_angle, '+');
		cast_h_ray(data, start, ray_angle, data->ray);
		cast_v_ray(data, start, ray_angle, data->ray);
		if (data->ray->h_ray.length < data->ray->v_ray.length)
			h_ray_set(data, ray_angle, data->ray);
		else
			v_ray_set(data, ray_angle, data->ray);
		draw_cub(data, ray_angle, rays);
		rays++;
	}
}
