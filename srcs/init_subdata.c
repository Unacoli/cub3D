/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_subdata.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:41:22 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/25 03:08:42 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_text(t_data *data, int nb, char *path)
{
	int	trash;
	int	width;
	int	height;

	data->text[nb].img = mlx_xpm_file_to_image(data->mlx, path,
			&width, &height);
	if (data->text[nb].img == NULL)
		exit_game(data, "Error\nFailed to make an image from xpm file", 1);
	data->text[nb].size.x = (double)width;
	data->text[nb].size.y = (double)height;
	data->text[nb].addr = mlx_get_data_addr(data->text[nb].img,
			&trash, &trash, &trash);
	data->text[nb].draw = (t_rgb *)data->text[nb].addr;
}

t_pos	point(int x, int y, char facing)
{
	t_pos	ret;

	ret.x = x;
	ret.y = y;
	ret.facing = facing;
	return (ret);
}

void	init_subdata(t_data *data)
{
	ft_memset(data->m_info, 0, sizeof(t_map));
	data->c_palette->red = get_rgb(255, 0, 0, 1);
	data->c_palette->white = get_rgb(255, 255, 255, 1);
	data->c_palette->black = get_rgb(0, 0, 0, 0);
	data->c_palette->blue = get_rgb(30, 144, 255, 0);
}