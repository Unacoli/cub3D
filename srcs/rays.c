/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/22 03:15:55 by tmoragli         ###   ########.fr       */
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
		if (my < data->m_info->size.y && my >= 0
			&& mx < data->map[my].len
			&& mx >= 0
			&& data->map[my].line[mx] == '1')
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

void	draw_line(t_data *data, int rays)
{
	double	y;
	double	x;
	double	tx_step;
	double	ty_step;
	double	ty;
	int		nb;

	nb = 0;
	
	x = rays * (WIDTH_3D / NB_RAYS) + data->m_info->size.x * 64;
	tx_step = 50 / data->line_height;
	ty_step = 50 / data->line_height;
	while (nb < WIDTH_3D / NB_RAYS)
	{
		y = HEIGHT_3D;
		ty = 0;
		if (data->tx >= 50)
			data->tx = 0;
		while (y >= 0)
		{
			if (y <= data->line_height + data->line_offset && y >= data->line_offset)
			{
				data->wall_color = get_pixel_color(data->text[data->wall], data->tx / 64 * 50, ty / 64 * 50);
				draw_pixel(data, x, y, data->wall_color, data->draw);
				ty += ty_step;
			}
			if (y > data->line_height + data->line_offset)
				draw_pixel(data, x, y, data->floor_color, data->draw);
			if (y < data->line_offset)
				draw_pixel(data, x, y, data->ceiling_color, data->draw);
			y--;
		}
		data->tx += tx_step;
		x++;
		nb++;
	}
}
