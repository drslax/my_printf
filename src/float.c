/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 05:36:56 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/18 04:38:10 by mherrat          ###   ########.fr       */
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
	n = n - 1023;
	return (n);
}

char	*int_mantis(t_64bit d)
{
	char	*n;
	char	*count;
	long	mantis;
	char	*tmp;
	int		mem;

	mantis = d.dfloat.mantis;
	n = ft_strdup("0");
	if ((mem = int_expo(d.dfloat.expo)) < 0)
		return (n);
	count = ft_strdup("1");
	mantis >>= (52 - mem);
	while (mem > 0 && mem--)
	{
		if (1 & mantis)
		{
			tmp = n;
			n = ft_strsum(n, count, 10);
			free(tmp);
		}
		tmp = count;
		count = ft_strmult(count, "2", 10);
		free(tmp);
		mantis >>= 1;
	}
	tmp = n;
	n = ft_strsum(n, count, 10);
	free(tmp);
	free(count);
	return (n);
}

void		ft_foisdix(char **str, int *len)
{
	char	*fois_dix;
	int		i;

	(*len)++;
	fois_dix = (char*)malloc(sizeof(char) * (*len + 1));
	fois_dix[*len] = '\0';
	i = -1;
	while ((*str)[++i] != '\0')
		fois_dix[i] = (*str)[i];
	fois_dix[i] = '0';
	free(*str);
	*str = fois_dix;
}

char	*ft_floating(int n, char **count)
{
	char	*i;
	int		len;
	char	*tmp;

	i = ft_strcnew(-n, '0');
	*count = ft_strdup("1");
	while (n++)
	{
		tmp = *count;
		*count = ft_strmult(*count, "5", 10);
		free(tmp);
	}
	tmp = i;
	i = ft_strsum(i, *count, 10);
	free(tmp);
	len = ft_strlen(i);
	tmp = *count;
	*count = ft_strmult(*count, "5", 10);
	free(tmp);
	ft_foisdix(&i, &len);
	return (i);
}

char		*float_mantis(t_64bit d)
{
	char		*n;
	char		*tmp;
	long		mantis;
	char		*count;
	int			i;
	int			len;

	mantis = reverse_bits(d.dfloat.mantis, 52);
	i = int_expo(d.dfloat.expo);
	count = NULL;
	if (i < 0 && i != -1023)
		n = ft_floating(i, &count);
	else if (i == -1023)
		return (ft_strcnew(1000, '0'));
	else
	{
		n = ft_strdup("0");
		count = ft_strdup("5");
	}
	while (i >= 0 && i--)
		mantis >>= 1;
	i = 52 - int_expo(d.dfloat.expo);
	while (i >= 0 && i--)
	{
		len = ft_strlen(n);
		if (1 & mantis)
		{
			tmp = n;
			n = ft_strsum(n, count, 10);
			free(tmp);
		}
		ft_foisdix(&n, &len);
		tmp = count;
		count = ft_strmult(count, "5", 10);
		free(tmp);
		mantis >>= 1;
	}
	free(count);
	return (n);
}

void		ft_printsignfloat(long sign, t_flags *flags, int **cursor)
{
	(**cursor)++;
	if (sign)
		ft_putchar('-');
	else if (flags->plus)
		ft_putchar('+');
	else if (flags->space)
		ft_putchar(' ');
}

int			ft_infini(t_64bit d, char **f, t_flags *flags, int **cursor)
{
	int		precision;
	int		size;
	int		expo;

	expo = int_expo(d.dfloat.expo);
//	flags->precision = 0;
	if (expo == 1024)
	{
		if (d.dfloat.mantis)
			*f = ft_strdup("nan");
		else if (!d.dfloat.mantis && d.dfloat.signe)
			*f = ft_strdup("-inf");
		else if (!d.dfloat.mantis && !d.dfloat.signe)
		{
			if (flags->plus)
				*f = ft_strdup("+inf");
			else if (flags->space)
				*f = ft_strdup(" inf");
			else
				*f = ft_strdup("inf");
		}
		size = (int)ft_strlen(*f);
		precision = (flags->precision < size)
			&& flags->precision != -1 ? size : size;
		**cursor += flags->width > precision ? flags->width : precision;
		if (size)
			flags->width -= precision;
	//	ft_printf("\n2nd width  = %d\n", flags->width);
		if (flags->la)
			flags->zero = 0;
	//	ft_printf("\nwidth  = %d\n", flags->width);
		while ((!flags->la || !(**f)) && --flags->width >= 0)
			ft_putchar(' ');
		ft_putstr(*f);
		while (--flags->width >= 0 && flags->la)
			ft_putchar(' ');
		return (0);
	}
	return (1);
}

void    ft_printfloat(va_list arg, int *cursor, t_flags flags)
{
	t_64bit		d;
	char		*f;
	char		*tmp;	
	char		*mant;
	char		*intt;
	char		*fmantis;
	int			precision;
	int			size;
	size_t		len;
	int			i;
	int			width;

	d.d = (double)va_arg(arg, double);
	if (ft_infini(d, &f, &flags, &cursor))
	{
		mant = int_mantis(d);
		i = 0;
		intt = ft_strsum(mant, "1", 10);
		len = ft_strlen(mant);
		fmantis = float_mantis(d);
		f = ft_strjoin(mant, fmantis);
		free(fmantis);
		width = flags.width;
		size = (int)ft_strlen(f);
		precision = (flags.precision != -1) ? flags.precision : 6;
		//ft_printf("\n - %d - \n", (ABS(d.dfloat.signe)));
		flags.width -= precision + len + 1;// + (ABS(d.dfloat.signe));
		if (flags.la)
			flags.zero = 0;
		if (d.dfloat.signe && (d.dfloat.signe = 1))
			flags.width--;
		if ((flags.plus || flags.space || d.dfloat.signe) && !flags.la && (flags.width < 0 || flags.zero))
		{
			ft_printsignfloat(d.dfloat.signe, &flags, &cursor);
			i = 1;
		}
		while (!flags.la && flags.width-- > ((flags.plus | flags.space) & !d.dfloat.signe))
		{
			(flags.zero) ? ft_putchar('0') : ft_putchar(' ');
			(*cursor)++;
		}
		if ((flags.plus || flags.space || d.dfloat.signe) && !i)
			ft_printsignfloat(d.dfloat.signe, &flags, &cursor);
		tmp = f;
		f = ft_strsub(f, 0, precision + len + 1); //leeeeeeakini//
		free(tmp);
		if (f[ft_strlen(f) - 1] > '5')
		{
			f[ft_strlen(f) - 1] = '\0';
			tmp = f;
			f = ft_strsum(f, "1", 10); //leeeeeakini
			free(tmp);
		}	
		if (f[ft_strlen(f) - 1] == '5' && ((f[ft_strlen(f) - 2] - '0') % 2))
		{

			f[ft_strlen(f) - 1] = '\0';
			tmp = f;
			f = ft_strsum(f, "1", 10); //leeeeeakini
			free(tmp);
		}
		i = 0;
		while (intt[i] == f[i])
			i++;
		if (i != 0 && len < ft_strlen(intt))
			len = ft_strlen(intt);
		precision += len;
		*cursor += precision;
		free(intt);
		tmp = f;
		while ((--precision >= 0 && *f))
		{
			if (!len--)
			{
				ft_putchar('.');
				(*cursor)++;
			}
			ft_putchar(*f++);
			if (flags.hash && flags.precision == 0 && !len)
			{
				ft_putchar('.');
				(*cursor)++;
			}
		}
		free(tmp);
		free(mant);
		while (flags.la && flags.width-- > ((flags.plus | flags.space) & !d.dfloat.signe))
		{
			flags.zero ? ft_putchar('0') : ft_putchar(' ');
			(*cursor)++;
		}
	}
}


























/*
   void    ft_printfloat(va_list arg, int *cursor, t_flags flags)
   {
   t_64bit		d;
   char		*f;
   char		*mant;
   char		*fmantis;

   d.d = (double)va_arg(arg, double);
   mant = int_mantis(d);
   fmantis = float_mantis(d);
   f = ft_strjoin(mant, fmantis);
   ft_putstr(f);
   free(f);
   free(fmantis);
   free(mant);
   (void)(*cursor);
   (void)flags.la;
   }
   unsigned long long	int_mantis(t_64bit d)
   {
   unsigned long long			n;
   long						mantis;
   unsigned long long			count;
   int							i;
   int							mem;

   n = 0;
   mantis = reverse_bits(d.dfloat.mantis, 52);
   count = 1;
   mem = int_expo(d.dfloat.expo);
   if ((i = mem) < 0)
   return (0);
   while (i >= 0 && i--)
   count *=2;
   n += count;
   count /=2;
//i = int_expo(d.dfloat.expo);
i = mem;
while (i >= 0 && i--)
{
n += (1 & mantis) ? count : 0;
count /= 2;
mantis >>= 1;
}
return (n);
}

char	*ft_floating(int n, char **count)
{
long long		i;
long long		c;
long long		nbr;

i = 1;
nbr = n;
while (nbr++)
i *= 5;
c = i * 5;
 *count = ft_itoa(c);
 i *= 10;
 ft_putchar('\n');
 ft_putnbr(i);
 ft_putchar('\n');
 return (ft_itoa(i));
 }


*/
