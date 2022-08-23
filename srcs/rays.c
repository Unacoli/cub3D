/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/23 02:47:31 by tmoragli         ###   ########.fr       */
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

	data->ray->h_ray.angle = ray_angle;
	dof = 0;
	if (data->ray->h_ray.angle > PI)
		setup_h_ray_data(&data->ray->h_ray, start, 1);
	if (data->ray->h_ray.angle < PI)
		setup_h_ray_data(&data->ray->h_ray, start, 0);
	if (data->ray->h_ray.angle == 0 || data->ray->h_ray.angle == PI)
		reset_ray_data(&data->ray->h_ray, start, &dof);
	send_ray(&data->ray->h_ray, data, dof, start);
}

void	cast_v_ray(t_data *data, t_pos start, double ray_angle)
{
	int	dof;

	data->ray->v_ray.angle = ray_angle;
	dof = 0;
	if (data->ray->v_ray.angle > P2 && data->ray->v_ray.angle < P3)
		setup_v_ray_data(&data->ray->v_ray, start, 1);
	if (data->ray->v_ray.angle < P2 || data->ray->v_ray.angle > P3)
		setup_v_ray_data(&data->ray->v_ray, start, 0);
	if (data->ray->v_ray.angle == P2 || data->ray->v_ray.angle == P3)
		reset_ray_data(&data->ray->v_ray, start, &dof);
	send_ray(&data->ray->v_ray, data, dof, start);
}

void	draw_line(t_data *data, int rays, t_text *text, t_draw *ray)
{
	double	y;
	double	x;

	x = rays * (WIDTH_3D / NB_RAYS) + data->m_info->size.x * 64;
	y = HEIGHT_3D;
	ray->ty = text->size.y - (ray->ty_offset * ray->ty_step);
	while (y >= 0)
	{
		if (y <= ray->line_height + ray->line_offset && y >= ray->line_offset)
		{
			ray->wall_color = get_pixel_color(data->text[ray->wall], ray->tx / 64 * text->size.x, ray->ty / 50 * text->size.y);
			draw_pixel(data, x, y, ray->wall_color, data->screen->draw);
			ray->ty -= ray->ty_step;
		}
		if (y > ray->line_height + ray->line_offset)
			draw_pixel(data, x, y, data->m_info->floor_color, data->screen->draw);
		if (y < ray->line_offset)
			draw_pixel(data, x, y, data->m_info->ceiling_color, data->screen->draw);
		y--;
	}
}
