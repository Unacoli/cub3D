/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:03:56 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/09 18:55:39 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include "../libft.h"
typedef struct s_parse
{
	char	flag;
	int		width;
	int		lwidth;
	char	precision;
	char	asterisk;
	int		lprecision;
	char	type;
	int		count;
	va_list	argptr;
}					t_parse;

int		ft_printf(const char *str, ...);
void	ft_parse(char **str, t_parse *parse);
void	ft_putnbr_base(int nbr, char *base, t_parse *parse);
void	ft_putnbr_base_2(long unsigned int nbr, char *base, t_parse *parse);
void	ft_s(t_parse *parse, char *s);
void	ft_d(t_parse *parse, int nb);
void	ft_hex(t_parse *parse, unsigned int nb);
void	ft_p(t_parse *parse, long unsigned int p);
void	ft_u(t_parse *parse, unsigned int u);
void	ft_printarray(char *str, t_parse *parse);
void	ft_printchar(char c, t_parse *parse);

#endif
