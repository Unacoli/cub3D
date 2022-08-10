/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:32:04 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/09 18:54:16 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_initialize(t_parse *parse)
{
	parse->flag = 0;
	parse->width = 0;
	parse->lwidth = 0;
	parse->precision = 0;
	parse->lprecision = 0;
	parse->asterisk = 0;
	parse->type = 0;
}

void	ft_flag(char **str, t_parse *parse)
{
	while (*str && **str && (**str == '-' || **str == '0'))
	{
		if (parse->flag != '-')
			parse->flag = **str;
		(*str)++;
	}
}

void	ft_width(char **str, t_parse *parse)
{
	if (ft_isdigit(**str))
	{	
		parse->width = 1;
		parse->lwidth = ft_atoi(*str);
	}
	while (*str && **str && ft_isdigit(**str))
		(*str)++;
}

void	ft_precision(char **str, t_parse *parse)
{
	if (**str == '.')
	{
		parse->precision = 1;
		(*str)++;
		parse->lprecision = ft_atoi(*str);
	}
	if (**str == '*')
	{
		parse->asterisk = 1;
		(*str)++;
		parse->lprecision = va_arg(parse->argptr, int);
	}
	while (*str && **str && ft_isdigit(**str))
		(*str)++;
}

void	ft_parse(char **str, t_parse *parse)
{
	ft_initialize(parse);
	ft_flag(str, parse);
	ft_width(str, parse);
	ft_precision(str, parse);
	parse->type = **str;
}
