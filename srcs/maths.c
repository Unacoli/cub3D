/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:32 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/16 13:53:23 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_rad(double	angle)
{
	return (angle * PI / 180);
}

double	get_angle(double rad)
{
	return (rad * 180 / PI);
}

double	get_dist(t_pos start, t_pos end)
{
	return (sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2)));
}

double	change_angle(double angle, double iterate, char iterator)
{
	if (iterator == '+')
	{
		if (angle + iterate < 360)
			return (angle + iterate);
		else if (angle + iterate > 360)
			return(angle + iterate - 360);
	}
	if (iterator == '-')
	{
		if (angle - iterate > 0)
			return (angle - iterate);
		else if (angle - iterate < 0)
			return(360 + angle - iterate);
	}
	return (angle);
}
