/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/19 03:30:50 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	send_ray(t_ray *ray, t_data *data, int dof, t_pos start)
{
	int	mx;
	int	my;

	while (dof < 16)
	{
		mx = (int)(ray->x / 64);
		my = (int)(ray->y / 64);
		if (mx < data->m_info->size.x && my < data->m_info->size.y
			&& mx >= 0 && my >= 0
			&& data->map[my][mx] == '1')
		{
			dof = 16;
			ray->length = get_dist(start, point(ray->x, ray->y, 0));
			return ;
		}
		else
		{
			ray->x += ray->x_dir;
			ray->y += ray->y_dir;
			dof++;
		}
	}
	ray->length = 8000;
}

void	cast_h_ray(t_data *data, t_pos start, double ray_angle)
{
	int	dof;

	data->h_ray.angle = ray_angle;
	dof = 0;
	if (data->h_ray.angle > PI)
		setup_h_ray_data(&data->h_ray, start, 1);
	if (data->h_ray.angle < PI)
		setup_h_ray_data(&data->h_ray, start, 0);
	if (data->h_ray.angle == 0 || data->h_ray.angle == PI)
		reset_ray_data(&data->h_ray, start, &dof);
	send_ray(&data->h_ray, data, dof, start);
}

void	cast_v_ray(t_data *data, t_pos start, double ray_angle)
{
	int	dof;

	data->v_ray.angle = ray_angle;
	dof = 0;
	if (data->v_ray.angle > P2 && data->v_ray.angle < P3)
		setup_v_ray_data(&data->v_ray, start, 1);
	if (data->v_ray.angle < P2 || data->v_ray.angle > P3)
		setup_v_ray_data(&data->v_ray, start, 0);
	if (data->v_ray.angle == P2 || data->v_ray.angle == P3)
		reset_ray_data(&data->v_ray, start, &dof);
	send_ray(&data->v_ray, data, dof, start);
}

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
		//	draw_ray(data, start, &data->h_ray, ray_angle);
			data->ray_length = data->h_ray.length;
			data->wall_color = data->red;
		}
		else
		{
		//	draw_ray(data, start, &data->v_ray, ray_angle);
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

void	draw_line(t_data *data, int rays)
{
	double	y;
	int		nb;
	double	x;

	nb = 0;
	x = rays * 8;
	while (nb < 8)
	{
		y = data->w_height;
		while (y > 0)
		{
			if (y <= data->line_height + data->line_offset && y > data->line_offset)
				draw_pixel(data, x, y, data->wall_color, data->draw_2d);
			if (y > data->line_height + data->line_offset)
				draw_pixel(data, x, y, data->floor_color, data->draw_2d);
			if (y < data->line_offset)
				draw_pixel(data, x, y, data->ceiling_color, data->draw_2d);
			y--;
		}
		x++;
		nb++;
	}
}