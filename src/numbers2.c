/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 00:36:25 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/01 20:53:02 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void		ft_printnumberoct(va_list arg, int *cursor, t_flags flags)
{
	unsigned long long	d;
	int				precision;
	int				size;

	ft_assigntypeu(arg, &d,flags);
	size = (int)ft_strlen(ft_itoa_base(d, 8, 0));
	precision = flags.precision > size
		? flags.precision : size;
	if (flags.precision <= size && flags.hash == 1 && d)
		precision++;
	*cursor += flags.width > precision ? flags.width :
	precision;
	flags.width -= precision;
	flags.zero = (flags.la || flags.width < 0
	|| precision > (size + 1)) ? 0 : flags.zero;
	while (flags.width-- > (flags.plus | flags.space) && !flags.la)
		(flags.zero && flags.precision == -1) ? ft_putchar('0') : ft_putchar(' ');
	while (precision-- > size)
		ft_putchar('0');
	if (flags.precision == 0 && d == 0)
		{
			if ((flags.width == -1 && !flags.space && !flags.plus))
				ft_putchar(' ');
			else if (flags.hash)
				ft_putchar('0');
			else if (!precision)	
				(*cursor)--;
		}
	else
		ft_putstr(ft_itoa_base(d, 8, 0));
	while (flags.width-- >= 0 && flags.la)
		flags.zero ? ft_putchar('0') : ft_putchar(' ');
}

void		ft_printnumberhexmin(va_list arg, int *cursor, t_flags flags)
{
	unsigned long long	d;
	int				precision;
	int				size;

	ft_assigntypeu(arg, &d,flags);
	size = (int)ft_strlen(ft_itoa_base(d, 16, 0));
	precision = flags.precision > size
		? flags.precision : size;
	flags.width = (flags.hash && d) ?  flags.width - 2 : flags.width ;

	*cursor += flags.width  > precision ? flags.width : precision;
	//ft_printf("CUR%dSOR::%d::##%d##", *cursor,flags.width,precision);
	//*cursor += flags.width > precision ? flags.width : precision;
	flags.width -= precision;
	//ft_printf("}%d{", flags.width);
	flags.zero = (flags.la || flags.width < 0
	|| precision > (size + 1)) ? 0 : flags.zero;
	while (!flags.la  && !(flags.zero && flags.precision == -1) && flags.hash && flags.width-- > (flags.plus | flags.space))
		ft_putchar(' ');
	//ft_printf("\n}%d{", flags.width);
	if (flags.hash && d)
		ft_hashprint(&cursor, 'x',flags);
	//ft_printf("}%d{\n", flags.width);
	while (!flags.la && flags.width-- > (flags.plus | flags.space))
		(flags.zero && flags.precision == -1) ? ft_putchar('0') : ft_putchar(' ');
	while (precision-- > size)
		ft_putchar('0');
	//(flags.precision == -1 && flags.zero && !flags.la && !d) ? ft_putchar('0') : ft_putchar(' ');
	
	
	if (!flags.precision && d == 0)
		{
			//ft_printf("}%d{\n", flags.width);
			if (!(flags.space | flags.plus | flags.la) && !flags.width)
				ft_putchar(' ');
			else if (!flags.la || (flags.la && flags.width == -1))
				(*cursor)--;
		}
	else
		{
			ft_putstr(ft_itoa_base(d, 16, 0));
			flags.width--;
		}
	

	while (flags.width-- >= (flags.plus | flags.space) && flags.la)
		flags.zero ? ft_putchar('0') : ft_putchar(' ');
}

void		ft_printnumberbin(va_list arg, int *cursor, t_flags flags)
{
	unsigned short int d;

	d = va_arg(arg, int);
	ft_putstr(ft_itoa_base(d, 2, 0));
	(*cursor)++;
	flags.zero = 0;
}

void		ft_printnumberhexmaj(va_list arg, int *cursor, t_flags flags)
{
	unsigned long long	d;
	int				precision;
	int				size;

	ft_assigntypeu(arg, &d,flags);
	size = (int)ft_strlen(ft_itoa_base(d, 16, 1));
	precision = flags.precision > size
		? flags.precision : size;
	flags.width = (flags.hash && d != 0) ?  flags.width - 2 : flags.width ;
	*cursor += flags.width > precision ? flags.width : precision;
	flags.width -= precision;
	flags.zero = (flags.la || flags.width < 0
	|| precision > (size + 1)) ? 0 : flags.zero;
	while (!flags.la && flags.width-- > (flags.plus | flags.space))
		(flags.zero && flags.precision == -1) ? ft_putchar('0') : ft_putchar(' ');
	if (flags.hash && d)
		ft_hashprint(&cursor, 'X',flags);
	while (!flags.la && --flags.width > (flags.plus | flags.space | flags.zero))
		(flags.zero && flags.precision == -1) ? ft_putchar('0') : 0;
	while (precision-- > size)
		ft_putchar('0');
	if (flags.precision == 0 && d == 0)
		{
			if ((flags.width == -1 && !flags.space && !flags.plus))
				ft_putchar(' ');
		/*	else if (flags.hash)
				ft_putchar('0');*/
			else if (!precision)	
				(*cursor)--;
		}
	else
		ft_putstr(ft_itoa_base(d, 16, 1));
	while (flags.width-- >= 0 && flags.la)
		flags.zero ? ft_putchar('0') : ft_putchar(' ');
}

void		ft_printadresse(va_list arg, int *cursor, t_flags flags)
{
	unsigned long ud;
	int				precision;
	int				size;

	ud = (unsigned long)va_arg(arg, void *);
	size = (int)ft_strlen(ft_itoa_base(ud, 16, 0));
	precision = flags.precision > size
		? flags.precision : size;
	*cursor += flags.width > precision ? flags.width :
	precision;
	flags.width -= precision + 2;
	flags.zero = (flags.la || flags.width < 0
	|| precision > (size + 1)) ? 0 : flags.zero;
	while (flags.width-- > (flags.plus | flags.space) && !flags.la && !flags.hash)
		(flags.zero && flags.precision == -1) ? ft_putchar('0') : ft_putchar(' ');
	if(flags.width < -1)
		(*cursor) += 2;
	ft_putstr("0x");
	while (precision-- > size)
		ft_putchar('0');
	if (flags.precision == 0 && ud == 0)
		{
			if ((flags.width == -1 && !flags.space && !flags.plus))
				ft_putchar(' ');
			else if (flags.hash)
				ft_putchar('0');
			else if (!precision)	
				(*cursor)--;
		}
	else
		ft_putstr(ft_itoa_base(ud, 16, 0));
	while (flags.width-- >= 0 && flags.la)
		flags.zero ? ft_putchar('0') : ft_putchar(' ');
}
