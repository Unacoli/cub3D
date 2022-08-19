/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_av.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nargouse <nargouse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 00:08:13 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/19 00:08:36 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	iscub(char *name_file)
{
	int	len;

	len = ft_strlen(name_file);
	if (name_file == 0)
		return (0);
	if (len < 5)
		return (0);
	if (ft_strncmp(name_file + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	check_av(int ac, char **av)
{
	if (ac != 2)
		return (ft_error("Usage: ./cub3D <*.cub>"));
	if (iscub(av[1]) == 0)
		return (ft_error("Use a .cub file"));
    return (0);
}