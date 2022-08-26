/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:42:03 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/26 23:06:55 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_id(char *str, int elems)
{
	if (str && (ft_strncmp(str, "NO ", 3) && ft_strncmp(str, "WE ", 3)
			&& ft_strncmp(str, "EA ", 3) && ft_strncmp(str, "SO ", 3)
			&& ft_strncmp(str, "C ", 2) && ft_strncmp(str, "F ", 2)))
	{
		if (elems < 6)
			return (printf("Error\nMissing %d elements\n", 6 - elems));
		else
			return (printf("Error\nNot a valid identifier: %s\n", str));
	}
	return (0);
}

t_list	*is_valid_id(t_list *file_line, t_data *data, int elems)
{
	char	*line;
	int		i;

	while (file_line && elems < 6)
	{
		i = 0;
		line = file_line->content;
		if (only_isspace(line))
		{
			file_line = file_line->next;
			continue ;
		}
		if (line && line[0] == ' ')
			line = ft_strtrim(line + 0 * i++, " ");
		if (check_id(line, elems) && i)
			return ((t_list *)swap_str(line, NULL));
		else if (stock_element(data, &elems, line))
			return (NULL);
		if (i)
			line = swap_str(line, NULL);
		file_line = file_line->next;
	}
	if (elems != 6)
		return (error_ret("Error\nElements missing"));
	return (file_line);
}
