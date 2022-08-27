/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/27 19:30:31 by tmoragli         ###   ########.fr       */
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

	while (dof < 2000)
	{
		mx = (int)(ray->x / SIZE_3D);
		my = (int)(ray->y / SIZE_3D);
		if (ray->y < 0)
			my = -1;
		if (ray->x < 0)
			mx = -1;
		if (is_inmap(data, mx, my) && data->map[my].line[mx] == '1')
		{
			dof = 2000;
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
