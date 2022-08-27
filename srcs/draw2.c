/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:30:07 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/27 19:34:29 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_horizon(t_data *data, double x, double y)
{
	while (y >= 0)
	{
		if (y >= HEIGHT_3D / 2)
			draw_pixel(data, x, y, data->m_info->floor_color);
		if (y < HEIGHT_3D / 2)
			draw_pixel(data, x, y, data->m_info->ceiling_color);
		y--;
	}
}

void	draw_cube(t_data *data, int rays, t_draw *ray)
{
	double	y;
	double	x;

	x = rays * (WIDTH_3D / NB_RAYS);
	y = HEIGHT_3D;
	while (y >= 0)
	{
		if (y <= ray->line_height + ray->line_offset && y >= ray->line_offset)
		{
			ray->wall_color = get_pixel_color(data->text[ray->wall],
					ray->tx, ray->ty);
			draw_pixel(data, x, y, ray->wall_color);
			ray->ty -= ray->ty_step;
		}
		if (y > ray->line_height + ray->line_offset)
			draw_pixel(data, x, y, data->m_info->floor_color);
		if (y < ray->line_offset)
			draw_pixel(data, x, y, data->m_info->ceiling_color);
		y--;
	}
}

void	draw_line(t_data *data, int rays, t_text *text, t_draw *ray)
{
	double	y;
	double	x;

	x = rays * (WIDTH_3D / NB_RAYS);
	y = HEIGHT_3D;
	ray->ty = text->size.y - 1 - (ray->ty_offset * ray->ty_step);
	ray->tx = ray->tx / SIZE_3D * text->size.x;
	if (data->ray->wall == 2 || data->ray->wall == 1)
		ray->tx = (text->size.x - ray->tx - 1);
	if (ray->h_ray.length == 8000 && ray->v_ray.length == 8000)
	{
		draw_horizon(data, x, y);
		return ;
	}
	else
		draw_cube(data, rays, ray);
}
