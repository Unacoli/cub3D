/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nargouse <nargouse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:46:41 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/19 13:32:17 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rgb	get_rgb(int r, int g, int b, int o)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.o = o;
	return (color);
}
