/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:17:11 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/09 18:55:39 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_node(t_parse *parse)
{
	if (parse->type == '%')
	{	
		write(1, "%", 1);
		parse->count++;
	}
	if (parse->type == 'c')
		ft_printchar(va_arg(parse->argptr, int), parse);
	if (parse->type == 's')
		ft_s(parse, va_arg(parse->argptr, char *));
	if (parse->type == 'p')
		ft_p(parse, va_arg(parse->argptr, long unsigned int));
	if (parse->type == 'd' || parse->type == 'i')
		ft_d(parse, va_arg(parse->argptr, int));
	if (parse->type == 'u')
		ft_u(parse, (unsigned int)va_arg(parse->argptr, unsigned int));
	if ((parse->type == 'x') || (parse->type == 'X'))
		ft_hex(parse, (unsigned int)va_arg(parse->argptr, unsigned int));
}

int	ft_printf(const char *str, ...)
{
	t_parse	*parse;
	int		count;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (0);
	parse->count = 0;
	va_start(parse->argptr, str);
	while (str && *str)
	{
		if (*str == '%')
		{
			str++;
			ft_parse((char **)&str, parse);
			ft_node(parse);
		}
		else
			ft_printchar(*str, parse);
		str++;
	}
	count = parse->count;
	free(parse);
	return (count);
}
