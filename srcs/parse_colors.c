/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:47:32 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/25 17:09:03 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rgb	get_pixel_color(t_text text, int x, int y)
{
	if ((x >= 0 && x <= text.size.x) && (y >= 0 && y <= text.size.y))
		return (text.draw[y * (int)text.size.x + x]);
	return (get_rgb(0, 0, 0, 0));
}

int	check_colors(t_data *data, char c)
{
	if (c == 'F')
	{
		if ((data->m_info->floor_color.r > 255
				|| data->m_info->floor_color.r < 0)
			|| (data->m_info->floor_color.g > 255
				|| data->m_info->floor_color.g < 0)
			|| (data->m_info->floor_color.b > 255
				|| data->m_info->floor_color.b < 0))
			return (ft_printf("Error\nWrong rgb for floor\n"));
	}
	else if (c == 'C')
	{
		if ((data->m_info->ceiling_color.r > 255
				|| data->m_info->ceiling_color.r < 0)
			|| (data->m_info->ceiling_color.g > 255
				|| data->m_info->ceiling_color.g < 0)
			|| (data->m_info->ceiling_color.b > 255
				|| data->m_info->ceiling_color.b < 0))
			return (ft_printf("Error\nWrong rgb for ceiling\n"));
	}
	return (0);
}

int	get_floor(t_data *data, char *rgb, int i)
{
	data->m_info->nb_f++;
	if (data->m_info->nb_f > 1)
		return (1);
	data->m_info->floor_color.r = ft_atoi(rgb);
	while (rgb && rgb[i] && ft_isdigit(rgb[i]))
		i++;
	data->m_info->floor_color.g = ft_atoi(rgb + (i + 1));
	while (rgb && rgb[i] && !ft_isdigit(rgb[i]))
		i++;
	while (rgb && rgb[i] && ft_isdigit(rgb[i]))
		i++;
	data->m_info->floor_color.b = ft_atoi(rgb + (i + 1));
	return (0);
}

int	get_ceiling(t_data *data, char *rgb, int i)
{
	data->m_info->nb_c++;
	if (data->m_info->nb_c > 1)
		return (1);
	data->m_info->ceiling_color.r = ft_atoi(rgb);
	while (rgb && rgb[i] && ft_isdigit(rgb[i]))
		i++;
	data->m_info->ceiling_color.g = ft_atoi(rgb + i + 1);
	while (rgb && rgb[i] && !ft_isdigit(rgb[i]))
		i++;
	while (rgb && rgb[i] && ft_isdigit(rgb[i]))
		i++;
	data->m_info->ceiling_color.b = ft_atoi(rgb + i + 1);
	return (0);
}

int	fetch_colors(t_data *data, char c, char *rgb)
{
	if (!rgb || ft_strlen(rgb) < 7)
	{
		ft_lstclear(&data->m_info->map, &free);
		exit_game(data, "Error\nMissing color in map", 1);
	}
	if (rgb[0] == ' ')
		rgb = swap_str(rgb, ft_strtrim(rgb, " "));
	if (c == 'F')
		if (get_floor(data, rgb, 0))
			return (1);
	if (c == 'C')
		if (get_ceiling(data, rgb, 0))
			return (1);
	return (check_colors(data, c));
}
