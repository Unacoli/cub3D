/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rescale_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:44:56 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/24 15:38:53 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pos	point_3d(double x, double y)
{
	t_pos	ret;

	ret.x = x / SIZE * SIZE_3D;
	ret.y = y / SIZE * SIZE_3D;
	return (ret);
}

t_pos	point_2d(double x, double y)
{
	t_pos	ret;

	ret.x = x / SIZE_3D * SIZE;
	ret.y = y / SIZE_3D * SIZE;
	return (ret);
}
