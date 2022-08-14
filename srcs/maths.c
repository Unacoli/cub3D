/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:24:32 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/14 16:24:54 by tmoragli         ###   ########.fr       */
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
