/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:50:22 by mherrat           #+#    #+#             */
/*   Updated: 2019/04/28 22:35:36 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"
/*DELETE LATER*/
#include <stdio.h>

/*DELETE LATER*/
void 		ft_printflags(t_flags flags)
{
	printf("\n---------------------\nflags.leftalign = %d\n", flags.la);
	printf("flags.space = %d\n", flags.space);
	printf("flags.plus = %d\n", flags.plus);
	printf("flags.hash = %d\n", flags.hash);
	printf("flags.length = %d\n", flags.length);
	printf("flags.width = %d\n", flags.width);
	printf("flags.precision = %d\n", flags.precision);
	printf("flags.zero = %d\n", flags.zero);
	printf("flags.hflag= %d\n", flags.hflag);
	printf("flags.lflag = %d\n", flags.lflag);
}

void		ft_initflags(t_flags *flags)
{
	flags->la = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->hash = 0;
	flags->length = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->zero = 0;
	flags->hflag = 0;
	flags->lflag = 0;
}

char		*detect_flg(char *string, va_list arg, int *cursor, t_flags *flags)
{
	string++;
	while (*string)
	{
		//printf("|%c|", *string);
		if (*string == '#' || *string == '0' || *string == ' ' || *string == '+'
				|| *string == '-' || (ft_atoi(string) != 0 && flags->width == 0)
				|| *string == '.' || *string == 'l' || *string == 'h' || *string == '*' || *string == 'z' || *string == 'j')
			ft_assignflag(arg, flags, &string);
		else if (detect_cnv_exist(string) != 0 || *string == '%')
		{
			if (*string == '%')
				ft_printpercent(cursor, *flags);
			else
				print_cnv(string, arg, cursor, *flags);
			//ft_printflags(*flags);
			ft_initflags(flags);
			return (string);
		}
		else if (*string == 'D' || *string == 'U' || *string == 'O' || *string == 'S' || *string == 'C')
		{
			flags->lflag = 1;
			if (*string == 'D')
				print_cnv("d", arg, cursor, *flags);
			else if (*string == 'U')
				print_cnv("u", arg, cursor, *flags);
			else if (*string == 'C')
				print_cnv("c", arg, cursor, *flags);
			else if (*string == 'S')
				print_cnv("s", arg, cursor, *flags);
			else
				print_cnv("o", arg, cursor, *flags);
			ft_initflags(flags);
			return (string);
		}
		string++;
	}
	return (string);
}

void		ft_assignflag(va_list arg, t_flags *flags, char **string)
{
	int		star;

	if (**string == '#')
		flags->hash = 1;
	else if (**string == '0')
		flags->zero = 1;
	else if (**string == ' ')
		flags->space = 1;
	else if (**string == '+')
		flags->plus = 1;
	else if (**string == '-')
		flags->la = 1;
	else if (**string == 'l' || **string == 'z' || **string == 'j')
		flags->lflag += 1;
	else if (**string == 'h')
		flags->hflag += 1;
	else if ((ft_atoi(*string) != 0 && flags->width == 0) || (**string == '0') )
	{
		flags->width = ft_atoi(*string);
		(*string) += (ft_numbersize(ft_atoi(*string))) - 1;
	}
	else if (**string == '.')
	{
		(*string)++;
		star = (**string == '*') ? va_arg(arg, int) : ft_atoi(*string);
		flags->precision = star;
		if ((**string == '*') || (**string == '0') || ft_atoi(*string) != 0)
			(*string) += (**string == '*')? 0 : (ft_numbersize(star)) - 1;
		else
			(*string)--;
	}
	else if (**string == '*')
	{
		star = va_arg(arg, int);
		flags->width = star;
	}	
}
