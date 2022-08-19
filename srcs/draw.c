/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:21:03 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/19 03:30:50 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_data *d, int x, int y, t_color color, t_color *draw)
{
	if (x >= 0 && x < d->w_width && y >= 0 && y < d->w_height)
		draw[y * d->w_width + x] = color;
}

void	draw_texture(t_data *data, t_pos pos, t_color color, int size, t_color *draw)
{
	double	x;
	double	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (x == 0 || x == size - 1 || y == 0 || y == size - 1)
				draw_pixel(data, x + pos.x, y + pos.y, data->black, draw);
			else
				draw_pixel(data, x + pos.x, y + pos.y, color, draw);
			x++;
		}
		y++;
	}
}

void	draw_ray(t_data *data, t_pos start, t_ray *ray, double ray_angle)
{
	double	t;
	double	length;

	t = ray_angle;
	ray->x_dir = cos(t);
	ray->y_dir = sin(t);
	ray->x = start.x;
	ray->y = start.y;
	length = 0;
	while (length < 8000 && get_dist(start, point(ray->x, ray->y, 0)) < ray->length)
	{
		draw_pixel(data, ray->x, ray->y, data->white, data->draw_2d);
		ray->y += ray->y_dir;
		ray->x += ray->x_dir;
		length++;
	}
}

void	map_fill(t_data *data)
{
	/*int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{	
			if (data->map[y][x] == '1')
				draw_texture(data, point(x * SIZE, y * SIZE, 0), data->floor_color, SIZE, data->draw_2d);
			if (data->map[y][x] == '0' || !is_player(data->map[y][x]))
				draw_texture(data, point(x * SIZE, y * SIZE, 0), data->ceiling_color, SIZE, data->draw_2d);
			x++;
		}
		y++;
	}*/
	raycasting(data, point(data->player.x * SIZE, data->player.y * SIZE, 0), 60);
	//draw_texture(data, point((data->player.x * SIZE - 8), (data->player.y * SIZE - 8), 0), data->red, 16, data->draw_2d);
}

void	image(t_data *data)
{
	map_fill(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_2d, 0, 0);
	//mlx_put_image_to_window(data->mlx, data->win, data->img_3d, 0, 0);
}
