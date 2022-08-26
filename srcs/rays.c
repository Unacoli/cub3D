/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/27 00:20:25 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rgb	get_pixel_color(t_text text, int x, int y)
{
	if ((x >= 0 && x <= text.size.x) && (y >= 0 && y <= text.size.y))
		return (text.draw[y * (int)text.size.x + x]);
	return (get_rgb(0, 0, 0, 0));
}

void	send_ray(t_ray *ray, t_data *data, int dof, t_pos start)
{
	int	mx;
	int	my;

	while (dof < 9000)
	{
		mx = (int)(ray->x / SIZE_3D);
		my = (int)(ray->y / SIZE_3D);
		if (my < data->m_info->size.y && my >= 0
			&& mx < data->map[my].len
			&& mx >= 0
			&& data->map[my].line[mx] == '1')
		{
			dof = 9000;
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


void	cast_h_ray(t_data *data, t_pos start, double ray_angle, t_draw *ray)
{
	int	dof;

	ray->h_ray.angle = ray_angle;
	dof = 0;
	if (ray->h_ray.angle > PI)
		setup_h_ray_data(&ray->h_ray, start, 1);
	if (ray->h_ray.angle < PI)
		setup_h_ray_data(&ray->h_ray, start, 0);
	if (ray->h_ray.angle == 0 || ray->h_ray.angle == PI)
		reset_ray_data(&ray->h_ray, start, &dof);
	send_ray(&ray->h_ray, data, dof, start);
}

void	cast_v_ray(t_data *data, t_pos start, double ray_angle, t_draw *ray)
{
	int	dof;

	ray->v_ray.angle = ray_angle;
	dof = 0;
	if (ray->v_ray.angle > (PI / 2)
		&& ray->v_ray.angle < ((3 * PI) / 2))
		setup_v_ray_data(&ray->v_ray, start, 1);
	if (ray->v_ray.angle < (PI / 2)
		|| ray->v_ray.angle > ((3 * PI) / 2))
		setup_v_ray_data(&ray->v_ray, start, 0);
	if (ray->v_ray.angle == (PI / 2)
		|| ray->v_ray.angle == ((3 * PI) / 2))
		reset_ray_data(&ray->v_ray, start, &dof);
	send_ray(&ray->v_ray, data, dof, start);
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
