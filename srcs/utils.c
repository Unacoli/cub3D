/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 00:35:30 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/12 17:03:48 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pos	point(int x, int y, char facing)
{
	t_pos	ret;

	ret.x = x;
	ret.y = y;
	ret.facing = facing;
	return (ret);
}
