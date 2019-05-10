/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 20:53:50 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/02 23:50:21 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int		int_expo(long expo)
{
	int		n;
	int		count;
	int		i;

	n = 0;
	count = 1;
	i = 12;
	while (--i)
	{
		n += (1 & expo) ? count : 0;
		count *= 2;
		ft_printf("%d\n",count);
		expo >>= 1;
	}
	return (n - 1023);
}
void    ft_printfloat(va_list arg, int *cursor, t_flags flags)
{
		t_64bit		d;
		int			expo;

		d.d = (double)va_arg(arg, double);
		expo = int_expo(d.dfloat.expo);
		ft_putnbr(expo);
		(void)(*cursor);
		(void)flags.la;
}
