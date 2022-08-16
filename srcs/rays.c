/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/16 16:53:00 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_h_ray_data(t_data *data, int facing, double precision, t_pos start)
{
	double	atang;

	data->h_ray.wall = 0;
	atang = -1 / tan(data->player.o);
	data->h_ray.y = (((int)start.y / 64) * 64) - precision;
	data->h_ray.x = (start.y - data->h_ray.y) * atang + start.x;
	data->h_ray.y_dir = 64 * facing;
	data->h_ray.x_dir = (-data->h_ray.y_dir) * atang;
}
void	set_v_ray_data(t_data *data, int facing, double precision, t_pos start)
{
	double	atang;

	data->v_ray.wall = 0;
	atang = tan(data->player.o) * -1;
	data->v_ray.x = (((int)start.x / 64) * 64) - precision;
	data->v_ray.y = (start.x - data->v_ray.x) * atang + start.y;
	data->v_ray.x_dir = 64 * facing;
	data->v_ray.y_dir = (-data->v_ray.x_dir) *atang;
}

int	closest_ray_to_wall(t_ray *r1, t_ray *r2)
{
	double	l1;
	double	l2;

	l1 = get_dist(point(r1->x, r1->y, 0), point(r1->goal.x, r1->goal.x, 0));
	l2 = get_dist(point(r2->x, r2->y, 0), point(r2->goal.x, r2->goal.x, 0));
	if (l1 > l2)
		return (2);
	return (1);
}

void	reset_ray_data(t_ray *ray, int *dof, t_pos start)
{
	ray->x = start.x;
	ray->y = start.y;
	*dof = 8;
}

int	next_raypoint(t_data *data, t_ray *ray)
{
	int	mx;
	int	my;

	mx = (int)(ray->x / 64);
	my = (int)(ray->y / 64);
	if (mx < data->m_info->size.x && my < data->m_info->size.y && mx >= 0 && my >= 0
		&& data->map[my][mx] == '1')
	{
		ray->wall = 1;
		ray->goal.x = mx * 64;
		ray->goal.y = my * 64;
		return (1);
	}
	ray->x += ray->x_dir;
	ray->y += ray->y_dir;
	return (0);
}

int	check_wall_hit(t_ray *r1, t_ray *r2)
{
	if (r1->wall)
		return (1);
	if (r2->wall)
		return (2);
	return (1);
}

int	send_ray(t_data *data, int dof)
{
	if (data->h_ray.wall == 1 && data->v_ray.wall == 1)
		return (closest_ray_to_wall(&data->h_ray, &data->v_ray));
	if (data->h_ray.wall == 1 || data->v_ray.wall == 1)
		return (check_wall_hit(&data->h_ray, &data->v_ray));
	while (dof < 8)
	{
		next_raypoint(data, &data->h_ray);
		next_raypoint(data, &data->v_ray);
		if (data->h_ray.wall == 1 && data->v_ray.wall == 1)
			return (closest_ray_to_wall(&data->h_ray, &data->v_ray));
		if (data->h_ray.wall == 1 || data->v_ray.wall == 1)
			return (check_wall_hit(&data->h_ray, &data->v_ray));
		dof++;
	}
	return (closest_ray_to_wall(&data->h_ray, &data->v_ray));
}

void	raycasting(t_data *data, t_pos start, int nb_rays)
{
	int		dof;

	data->v_ray.angle = get_rad(data->player.o);
	data->h_ray.angle = data->v_ray.angle;
	while (nb_rays > 0)
	{
		dof = 0;
		if (data->h_ray.angle > PI)
			set_h_ray_data(data, -1, 0.0001, start);
		if (data->h_ray.angle < PI)
			set_h_ray_data(data, 1, -64, start);
		if (data->h_ray.angle == 0 || data->h_ray.angle == PI)
			reset_ray_data(&data->h_ray, &dof, start);
		if (data->v_ray.angle > P2 && data->v_ray.angle < P3)
			set_v_ray_data(data, -1, 0.0001, start);
		if (data->v_ray.angle < P2 || data->v_ray.angle > P3)
			set_v_ray_data(data, -1, -64, start);
		if (data->v_ray.angle == P2 || data->player.o == P3)
			reset_ray_data(&data->v_ray, &dof, start);
		int ret = send_ray(data, dof);
		(void)ret;
		/*if (ret == 1)
			draw_ray(data, start, data->h_ray);
		if (ret == 2)
			draw_ray(data, start, data->v_ray);*/
		
		nb_rays--;
	}
}

void	draw_ray(t_data *data, t_pos start, t_ray ray)
{
	double	t;
	double	x_dir;
	double	y_dir;
	double	y;
	double	x;

	t = get_rad(data->player.o);
	x_dir = cos(t);
	y_dir = sin(t);
	x = start.x;
	y = start.y;
	if (ray.angle < PI)
	{
		while (y > ray.goal.y)
		{
			draw_pixel(data, x, y, data->white);
			x += x_dir;
			y += y_dir;
		}
		return ;
	}
	/*if (ray.angle > PI)
	{
		while (y < ray.goal.y)
		{
			draw_pixel(data, x, y, data->white);
			x += x_dir;
			y += y_dir;
		}
		return ;
	}
	if (ray.angle > P2 && ray.angle < P3)
	{
		while (x > ray.goal.x)
		{
			draw_pixel(data, x, y, data->white);
			x += x_dir;
			y += y_dir;
		}
		return ;
	}
	if (ray.angle < P2 || ray.angle > P3)
	{
		while (x < ray.goal.x)
		{
			draw_pixel(data, x, y, data->white);
			x += x_dir;
			y += y_dir;
		}
		return ;
	}*/
}
