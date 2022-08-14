/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:12:39 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/14 16:25:27 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cube_start(t_data *data)
{
	if (parse_map(data, 0))
		return (ft_error("File error, check description above"));
	else
		start_game(data);
	return (0);
}