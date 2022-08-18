/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/18 16:08:18 by tmoragli         ###   ########.fr       */
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
		if (mx < data->m_info->size.x && my < data->m_info->size.y && mx >= 0 && my >= 0
			&& data->map[my][mx] == '1')
		{
			dof = 16;
			ray->length = get_dist(start, point(ray->x, ray->y, 0));
			//draw_texture(data, point(ray->x, ray->y, 0), data->player_color, 8);
			return ;
		}
		else
		{
			//draw_texture(data, point(ray->x, ray->y, 0), data->player_color, 8);
			ray->x += ray->x_dir;
			ray->y += ray->y_dir;
			dof++;
		}
	}
	ray->length = 8000;
}

void	setup_h_ray_data(t_ray *ray, t_pos start, int facing)
{
	double	atang;

	atang = -1 / tan(ray->angle);
	if (facing)
	{
		ray->y = (((int)start.y / 64) * 64) - 0.0001;
		ray->x = (start.y - ray->y) * atang + start.x;
		ray->y_dir = -64;
		ray->x_dir = (ray->y_dir * -1) * atang;
	}
	else
	{
		ray->y = (((int)start.y / 64) * 64) + 64;
		ray->x = (start.y - ray->y) * atang + start.x;
		ray->y_dir = 64;
		ray->x_dir = (ray->y_dir * -1) * atang;
	}
}

void	setup_v_ray_data(t_ray *ray, t_pos start, int facing)
{
	double	atang;

	atang = tan(ray->angle) * -1;
	if (facing)
	{
		ray->x = (((int)start.x / 64) * 64) - 0.0001;
		ray->y = (start.x - ray->x) * atang + start.y;
		ray->x_dir = -64;
		ray->y_dir = (ray->x_dir * -1) * atang;
	}
	else
	{
		ray->x = (((int)start.x / 64) * 64) + 64;
		ray->y = (start.x - ray->x) * atang + start.y;
		ray->x_dir = 64;
		ray->y_dir = (ray->x_dir * -1) * atang;
	}
}

void	reset_ray_data(t_ray *ray, t_pos start, int *dof)
{
	ray->x = start.x;
	ray->y = start.y;
	*dof = 16;
}

void	cast_h_ray(t_data *data, t_pos start, double ray_angle)
{
	int	dof;

	data->h_ray.angle = get_rad(ray_angle);
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

	data->v_ray.angle = get_rad(ray_angle);
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
	double	first_ray_angle;
	double	ray_angle;

	first_ray_angle = change_angle(data->player.o, 0.1 * 360, '-');
	ray_angle = data->player.o;
	while (nb_rays > 0)
	{
		cast_h_ray(data, start, ray_angle);
		cast_v_ray(data, start, ray_angle);
		if (data->h_ray.length < data->v_ray.length)
			draw_ray(data, start, &data->h_ray, ray_angle);
		else
			draw_ray(data, start, &data->v_ray, ray_angle);
		ray_angle = change_angle(first_ray_angle, 0.1 * nb_rays, '+');
		nb_rays--;
	}
}

void	draw_ray(t_data *data, t_pos start, t_ray *ray, double ray_angle)
{
	double	t;
	double	x_dir;
	double	y_dir;
	double	y;
	double	x;
	double	length;
	double	draw_length;

	t = get_rad(ray_angle);
	x_dir = cos(t);
	y_dir = sin(t);
	x = start.x;
	y = start.y;
	length = 0;
	draw_length = 0;
	while (length < 8000 && draw_length < ray->length)
	{
		draw_pixel(data, x, y, data->white);
		y += y_dir;
		x += x_dir;
		draw_length = get_dist(start, point(x, y, 0));
		length++;
	}
}