/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 05:36:56 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/10 05:51:08 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

long	reverse_bits(long b, int bit_len)
{
	long	r;

	r = 0;
	while (bit_len--)
	{
		r = (r << 1) | (b & 1);
		b >>= 1;
	}
	return (r);
}

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
		expo >>= 1;
	}
	return (n - 1023);
}

unsigned long long	int_mantis(t_64bit d)
{
	unsigned long long			n;
	long						mantis;
	unsigned long long			count;
	int							i;

	n = 0;
	mantis = reverse_bits(d.dfloat.mantis, 52);
	count = 1;
	i = int_expo(d.dfloat.expo);
	while (i--)
		count *=2;
	n += count;
	count /=2;
	i = int_expo(d.dfloat.expo);
	while (i--)
	{
		n += (1 & mantis) ? count : 0;
		count /= 2;
		mantis >>= 1;
	}
	return (n);
}

char		*float_mantis(t_64bit d)
{
	char		*n,*tmp;
	long		mantis;
	char		*count;
	int			i;

	n = ft_strdup("0");
	count = ft_strdup("5");
	mantis = reverse_bits(d.dfloat.mantis, 52);
	i = int_expo(d.dfloat.expo);
	while (i--)
		mantis >>= 1;
	i = 52 - int_expo(d.dfloat.expo);
	while (i--)
	{
		if (1 & mantis)
		{
			tmp = n;
			n = ft_strsum(n, count, 10);
			free(tmp);
		}
		tmp = n;
		n = ft_strmult(n, "10", 10);
		free(tmp);
		tmp = count;
		count = ft_strmult(count, "5", 10);
		free(tmp);
//		(1 & mantis) ? ft_putnbr(1) : ft_putnbr(0); ft_putchar('\n');
		mantis >>= 1;
	}
	return (n);
}

void    ft_printfloat(va_list arg, int *cursor, t_flags flags)
{
	t_64bit		d;
	char		*f;
	int			mantis;
	char		*mant;
	char		*fmantis;

	d.d = (double)va_arg(arg, double);
	mantis = int_mantis(d);
	mant = ft_itoa(mantis);
	fmantis = float_mantis(d);
	f = ft_strjoin(mant, fmantis);
	free(mant);
	free(fmantis);
	ft_putstr(f);
	free(f);
//	ft_putstr(fmantis);
	(void)(*cursor);
	(void)flags.la;
}
