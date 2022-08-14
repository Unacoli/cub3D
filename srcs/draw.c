/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:21:03 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/14 22:10:38 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_data *d, int x, int y, t_color color)
{
	if (x >= 0 && x < d->w_width && y >= 0 && y < d->w_height)
		d->draw[y * d->w_width + x] = color;
}

void	draw_texture(t_data *data, t_pos pos, t_color color, int size)
{
	double	x;
	double	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			draw_pixel(data, x + pos.x, y + pos.y, color);
			x++;
		}
		y++;
	}
}

void	map_fill(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	draw_ceiling(data);
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{	
			if (data->map[y][x] == '1')
				draw_texture(data, point(x * SIZE, y * SIZE, 0), data->floor_color, SIZE);
			x++;
		}
		y++;
	}
	draw_texture(data, point((data->player.x * SIZE - 8), (data->player.y * SIZE - 8), 0), data->player_color, 16);
	send_ray(data, point(data->player.x * SIZE, data->player.y * SIZE, 0));
}

void	draw_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->w_height)
	{
		x = 0;
		while (x < data->w_width)
		{
			draw_pixel(data, x, y, data->ceiling_color);
			x++;
		}
		y++;
	}
}

void	image(t_data *data)
{
	map_fill(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}