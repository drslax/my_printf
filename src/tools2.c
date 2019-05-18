/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:13:25 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/09 02:50:19 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int			ft_getvaluex(t_flags *fl, int **cursor, int size
		, long unsigned int d)
{
	int precision;

	precision = 0;
	if (fl->precision || d != 0)
		precision = fl->precision > size ? fl->precision : size;
	fl->width = (fl->hash && d) ? fl->width - 2 : fl->width;
	**cursor += fl->width > precision ? fl->width : precision;
	precision = fl->precision > size ? fl->precision : size;
	fl->width -= precision;
	fl->zero = (fl->la || fl->width < 0 || precision > (size + 1))
		? 0 : fl->zero;
	return (precision);
}

int			ft_getvalueo(t_flags *fl, int **cursor, int size
		, long unsigned int d)
{
	int precision;

	precision = fl->precision > size ? fl->precision : size;
	if (fl->precision <= size && fl->hash == 1 && d)
		precision++;
	else if (!fl->precision && !fl->width && !fl->hash && d == 0)
		precision = 0;
	**cursor += fl->width > precision ? fl->width : precision;
	fl->width -= precision;
	fl->zero = (fl->la || fl->width < 0 || precision > (size + 1))
		? 0 : fl->zero;
	return (precision);
}

int			ft_getvaluead(t_flags *fl, int **cursor, int size)
{
	int precision;

	precision = fl->precision > size ? fl->precision : size;
	**cursor += fl->width > precision ? fl->width : precision;
	fl->width -= precision + 2;
	fl->zero = (fl->la || fl->width < 0 || precision > (size + 1))
		? 0 : fl->zero;
	while (fl->width-- > (fl->plus | fl->space) && !fl->la && !fl->hash)
		(fl->zero && fl->precision == -1) ? ft_putchar('0') : ft_putchar(' ');
	return (precision);
}
