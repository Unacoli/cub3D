/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 00:35:46 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/16 16:44:19 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_id(char *str)
{
	if (str && (ft_strncmp(str, "NO ", 3) && ft_strncmp(str, "WE ", 3)
			&& ft_strncmp(str, "EA ", 3) && ft_strncmp(str, "SO ", 3)
			&& ft_strncmp(str, "C ", 2) && ft_strncmp(str, "F ", 2)))
		return (ft_printf("Error\nNot a valid identifier: %s\n", str));
	return (0);
}

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

void	stock_element(t_data *data, int *elems, char *line)
{
	*elems += 1;
	if (!ft_strncmp(line, "NO ", 3))
		data->m_info->no_path = ft_substr(line, 3, ft_strlen(line) - 3);
	if (!ft_strncmp(line, "EA ", 3))
		data->m_info->ea_path = ft_substr(line, 3, ft_strlen(line) - 3);
	if (!ft_strncmp(line, "SO ", 3))
		data->m_info->so_path = ft_substr(line, 3, ft_strlen(line) - 3);
	if (!ft_strncmp(line, "WE ", 3))
		data->m_info->we_path = ft_substr(line, 3, ft_strlen(line) - 3);
	if (!ft_strncmp(line, "F ", 2))
		fetch_colors(data, 'F', ft_substr(line, 2, ft_strlen(line) - 1));
	if (!ft_strncmp(line, "C ", 2))
		fetch_colors(data, 'C', ft_substr(line, 2, ft_strlen(line) - 1));
}

t_list	*is_valid_id(t_list *file_line, t_data *data)
{
	int		elems;
	char	*line;

	elems = 0;
	while (file_line && elems < 6)
	{
		line = file_line->content;
		if (line && ft_isspace(line[0]))
			swap_str(line, ft_strtrim(line, " \t\r\v\f\n"));
		if (check_id(line))
			return (NULL);
		else
			stock_element(data, &elems, line);
		file_line = file_line->next;
	}
	if (elems != 6)
	{
		ft_printf("Error\nNot all elements were disposed, missing %d\n",
			6 - elems);
		return (NULL);
	}
	return (file_line);
}

int		find_map_width(char **map)
{
	int	i;
	int	row_len;

	row_len = 0;
	i =0;
	while (map && map[i])
	{
		if ((int)ft_strlen(map[i]) > row_len)
			row_len = ft_strlen(map[i]);
		i++;
	}
	return (row_len);
}

void	fill_map_array(t_data *data, t_list *map)
{
	int		i;
	char	*line;

	i = 0;
	while (map)
	{
		line = (char *)(map->content);
		data->map[i] = ft_strdup(line);
		i++;
		map = map->next;
	}
	data->m_info->size.y = str_arr_size(data->map);
	data->m_info->size.x = find_map_width(data->map);
}

int	scan_map(char **map, t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map && map[y][x])
		{
			if (!is_player(map[y][x]))
			{
				data->player = point(x, y, map[y][x]);
				data->nb_player++;
			}
			if (data->nb_player > 1)
				return (ft_printf("Error\nToo many player elements, line: %d column: %d\n",
						y, x));
			if (check_elem(map, x, y, str_arr_size(map)))
				return (1);
			x++;
		}
		y++;
	}
	if (data->nb_player < 1)
		return (ft_printf("Error\nNo player on map, (N, S, W, E)\n"));
	return (0);
}

void	trim_textures(t_data *data)
{
	if (ft_strchr(data->m_info->no_path, ' '))
		data->m_info->no_path = swap_str(data->m_info->no_path, ft_strtrim(data->m_info->no_path, " "));
	if (ft_strchr(data->m_info->ea_path, ' '))
		data->m_info->ea_path = swap_str(data->m_info->ea_path, ft_strtrim(data->m_info->ea_path, " "));
	if (ft_strchr(data->m_info->we_path, ' '))
		data->m_info->we_path = swap_str(data->m_info->we_path, ft_strtrim(data->m_info->we_path, " "));
	if (ft_strchr(data->m_info->so_path, ' '))
		data->m_info->so_path = swap_str(data->m_info->so_path, ft_strtrim(data->m_info->so_path, " "));
}

int	parse_map(t_data *data, int fd)
{
	int		ret;
	char	*line;

	ret = 0;
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
		return (ft_error("No map given, couldn't open file"));
	while (get_next_line(fd, &line))
	{
		if (!only_isspace(line))
		{
			ft_lstadd_back(&(data->m_info->map), ft_lstnew(line));
			ft_printf("%s\n", line);
		}
		else
			free(line);
	}
	ft_lstadd_back(&(data->m_info->map), ft_lstnew(line));
	ft_printf("%s\n", line);
	if (is_valid_file(data))
		ret++;
	ft_lstclear(&data->m_info->map, &free);
	return (ret);
}
