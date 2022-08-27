/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 13:43:14 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/27 13:48:29 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (1);
	return (0);
}

int	is_inmap(t_data *data, int x, int y)
{
	if (y >= 0 && y < data->m_info->size.y && x >= 0 && x <= data->map[y].len)
		return (1);
	return (0);
}
