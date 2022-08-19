/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nargouse <nargouse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:47:32 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/19 13:37:48 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_colors(t_data *data, char c)
{
	if (c == 'F')
	{
		if ((data->floor_color.r > 255
				|| data->floor_color.r < 0)
			|| (data->floor_color.g > 255
				|| data->floor_color.g < 0)
			|| (data->floor_color.b > 255
				|| data->floor_color.b < 0))
			return (ft_printf("Error\nWrong rbg for floor\n"));
		if ((data->ceiling_color.r > 255
				|| data->ceiling_color.r < 0)
			|| (data->ceiling_color.g > 255
				|| data->ceiling_color.g < 0)
			|| (data->ceiling_color.b > 255
				|| data->ceiling_color.b < 0))
			return (ft_printf("Error\nWrong rbg for ceiling\n"));
	}
	return (0);
}

void	get_floor(t_data *data, char *rgb, int i)
{
	data->floor_color.r = ft_atoi(rgb);
	while (rgb && rgb[i] && ft_isdigit(rgb[i]))
		i++;
	data->floor_color.g = ft_atoi(rgb + (i + 1));
	while (rgb && rgb[i] && !ft_isdigit(rgb[i]))
		i++;
	while (rgb && rgb[i] && ft_isdigit(rgb[i]))
		i++;
	data->floor_color.b = ft_atoi(rgb + (i + 1));
}

void	get_ceiling(t_data *data, char *rgb, int i)
{
	data->ceiling_color.r = ft_atoi(rgb);
	while (rgb && rgb[i] && ft_isdigit(rgb[i]))
		i++;
	data->ceiling_color.g = ft_atoi(rgb + i + 1);
	while (rgb && rgb[i] && !ft_isdigit(rgb[i]))
		i++;
	while (rgb && rgb[i] && ft_isdigit(rgb[i]))
		i++;
	data->ceiling_color.b = ft_atoi(rgb + i + 1);
}

int	fetch_colors(t_data *data, char c, char *rgb)
{
	if (!rgb)
		exit_game(data, "Error\nAllocation failure\n");
	if (rgb[0] == ' ')
		rgb = swap_str(rgb, ft_strtrim(rgb, " "));
	if (c == 'F')
		get_floor(data, rgb, 0);
	if (c == 'C')
		get_ceiling(data, rgb, 0);
	free(rgb);
	return (check_colors(data, c));
}
