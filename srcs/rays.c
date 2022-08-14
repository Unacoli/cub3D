/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:01 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/14 22:34:22 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	send_ray(t_data *data, t_pos start_point)
{
	double	t;
	int		length;

	length = 0;
	t = get_rad(data->player.o);
	data->ray.x_dir = cos(t);
	data->ray.y_dir = sin(t);
	data->ray.x = start_point.x;
	data->ray.y = start_point.y;
	while (length < 100)
	{
		draw_pixel(data, data->ray.x + data->ray.x_dir * length, data->ray.y + data->ray.y_dir * length, data->white);
		length++;
	}
}
