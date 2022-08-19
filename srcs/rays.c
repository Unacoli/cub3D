/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/19 16:12:13 by tmoragli         ###   ########.fr       */
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

void	draw_line(t_data *data, int rays)
{
	double	y;
	double	x;
	int		nb;

	nb = 0;
	x = data->w_width - 480 + rays * 1;
	while (nb < 1)
	{
		y = 320;
		while (y >= 0)
		{
			if (y < data->line_offset)
				draw_pixel(data, x, y, data->ceiling_color, data->draw);
			else if (y <= data->line_height + data->line_offset
				&& y > data->line_offset)
				draw_pixel(data, x, y, data->wall_color, data->draw);
			else if (y > data->line_height)
				draw_pixel(data, x, y, data->floor_color, data->draw);
			y--;
		}
		x++;
		nb++;
	}
}
