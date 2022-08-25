/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nargouse <nargouse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:13:10 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/25 22:13:20 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_numbers(char *rgb)
{
    int i;

    i = 0;
    while (rgb[i])
    {
        if (!ft_isdigit(rgb[i]) && rgb[i] != ',' && rgb[i] != ' ')
            return (1);
        i++;
    }
    return (0);
}

int check_space(char *rgb)
{
    int n;

    n = 0;
    if (ft_strlen(rgb) < 1)
        return (0);
    n = ft_strlen(rgb) - 1;
    if (rgb[n] == ' ')
    {
        while (rgb[n] == ' ')
            n--;
        rgb[n + 1] = '\0';
    }
    return (0);
}

int check_format(char *rgb)
{
    int i;
    int coma;

    coma = 0;
    i = 0;
    while (rgb[i])
    {
        coma = 0;
        while (ft_isdigit(rgb[i]))
            i++;
        while (rgb[i] == ' ' || rgb[i] == ',')
        {
            if (rgb[i] == ',')
                coma++;
            i++;
            if (coma != 1)
                return (1);
        }
    }
    return (0);
}

int check_coma(char *rgb)
{
    int i;
    int coma;

    i = 0;
    coma = 0;
    while (rgb[i])
    {
        if (rgb[i] == ',')
            coma++;
        i++;
    }
    if (coma != 2)
        return (1);
    return (0);
}
