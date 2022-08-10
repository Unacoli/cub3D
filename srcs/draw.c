/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:15:00 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/09 22:22:38 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_data *d, int x, int y, t_color color)
{
	if (color.o == 0 && (x >= 0 && x < d->width) && (y >= 0 && y < d->height))
		d->draw[y * d->width + x] = color;
}

t_color	convert_color(char r, char g, char b, char o)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.o = o;
	return (color);
}
