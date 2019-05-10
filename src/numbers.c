/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:50:29 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/01 03:48:03 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"
#include <stdio.h>
int		ft_numbersize(unsigned long long number)
{
	int i;

	i = 1;
	while (number /= 10)
		i++;
	return (i);
}

void	ft_putunbr(unsigned long long nbr)
{
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + '0');
	}
	else
		ft_putchar(nbr + '0');
}

void	ft_assigntype(va_list arg, long long *number, t_flags flags)
{
	if (flags.lflag == 1) 
		*number = va_arg(arg, long);
	else if (flags.lflag > 1)
		*number = va_arg(arg, long long);
	else if (flags.lflag == 0) 
		*number = va_arg(arg, int);
	else if (flags.hflag == 1)
		*number = (short)va_arg(arg, int);
	else if (flags.hflag == 2)
		*number = (char)va_arg(arg, int);
}

void	ft_assigntypeu(va_list arg, unsigned long long *number, t_flags flags)
{
	if (flags.lflag == 1) 
		*number = (unsigned long)va_arg(arg, unsigned long);
	else if (flags.lflag > 1)
		*number = (unsigned long long)va_arg(arg, unsigned long long);
	else if (flags.lflag == 0) 
		*number = va_arg(arg, unsigned int);
	else if (flags.hflag == 1)
		*number = (unsigned short)va_arg(arg, unsigned int);
	else if (flags.hflag == 2)
		*number = (unsigned char)va_arg(arg, unsigned int);
}

void	ft_printsign(int number, t_flags flags)
{
	if (number < 0)
		ft_putchar('-');
	else if (flags.plus)
		ft_putchar('+');
	else if (flags.space)
		ft_putchar(' ');
}

void	ft_printnumber(va_list arg, int *cursor, t_flags flags)
{
	long long	d;
	int			precision;
	int			sign;

	ft_assigntype(arg, &d,flags);
	sign = d < 0 ? 1 : 0;
	if ((flags.plus || flags.la || flags.space) && flags.width && !flags.precision && d == 0)
		precision = 0;
	else
		precision = flags.precision > ft_numbersize(ABS(d))
		? flags.precision : ft_numbersize(ABS(d));	
	*cursor += flags.width > precision ? flags.width :
	precision + (sign | flags.plus | flags.space);
	flags.width -= precision;
	flags.zero = (flags.la || flags.width < 0
	|| precision > ft_numbersize(ABS(d))) ? 0 : flags.zero;
	if (flags.zero && flags.precision)
		if((flags.hflag == 2 && flags.precision == -1) || flags.hflag != 2)
			ft_printsign(d, flags);
	while (flags.width-- > (sign | flags.plus | flags.space) && !flags.la)
		(flags.zero && flags.precision == -1) ? ft_putchar('0') : ft_putchar(' ');
	if (flags.plus || flags.space || d < 0)
		if (!flags.zero || (flags.hflag == 2 && flags.precision != -1) || ((flags.plus || flags.zero) && !flags.precision))
			ft_printsign(d, flags);
	while (precision-- > ft_numbersize(ABS(d)))
		ft_putchar('0');
	if (flags.precision == 0 && d == 0)
		{
			if ((flags.width == -1 && !flags.space && !flags.plus))
				ft_putchar(' ');
			else if (!precision)	
				(*cursor)--;
		}
	else
		ft_putnbr(ABS(d));
	while (flags.width-- >= (sign | flags.plus | flags.space) && flags.la)
		flags.zero ? ft_putchar('0') : ft_putchar(' ');
}

void	ft_printnumberu(va_list arg, int *cursor, t_flags flags)
{
	unsigned long long	d;
	int				precision;

	ft_assigntypeu(arg, &d,flags);
	precision = flags.precision > ft_numbersize(d)
		? flags.precision : ft_numbersize(d);
	*cursor += flags.width > precision ? flags.width :
	precision;
	flags.width -= precision;
	flags.zero = (flags.la || flags.width < 0
	|| precision > ft_numbersize(d)) ? 0 : flags.zero;
	while (flags.width-- > (flags.plus | flags.space) && !flags.la)
		(flags.zero && flags.precision == -1) ? ft_putchar('0') : ft_putchar(' ');
	while (precision-- > ft_numbersize(d))
		ft_putchar('0');
	//ft_putunbr(d);
	if (flags.precision == 0 && d == 0)
		{
			if ((flags.width == -1 && !flags.space && !flags.plus))
				ft_putchar(' ');
			else if (!precision)	
				(*cursor)--;
		}
	else
		ft_putunbr(d);
	while (flags.width-- >= 0 && flags.la)
		flags.zero ? ft_putchar('0') : ft_putchar(' ');
}
