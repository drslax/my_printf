/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:50:55 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/02 22:00:46 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define ABS(Value) (Value<0) ? Value * -1 : Value
# include "../src/libft/libft.h"
# include <stdarg.h>

typedef	struct	s_flags
{
	int			width;
	int			length;
	int			la;
	int			plus;
	int			hash;
	int			zero;
	int			space;
	int			precision;
	int			hflag;
	int			lflag;
}				t_flags;

typedef struct	s_double
{
	long		mantis:52;
	long		expo:11;
	long		signe:1;
}				t_double;

typedef union	u_64bit
{
	double		d;
	t_double	dfloat;
}				t_64bit;

typedef struct	s_ldouble
{
	long		mantis:63;
	long		int_part:1;
	long		expo:15;
	long		signe:1;
}				t_ldouble;

typedef union	u_80bit
{
	long double		ld;
	t_ldouble		ldouble;
}				t_80bit;


typedef enum	e_cnv
{
	O_s,
	O_d,
	O_i,
	O_u,
	O_o,
	O_x,
	O_X,
	O_b,
	O_c,
	O_p,
	O_f,
	O_END
}				t_cnv;

typedef struct	s_func
{
	char	cnv_type;
	t_cnv	cnv;
	void	(*f)(va_list arg, int *cursor, t_flags flags);
}				t_func;

t_func			call_func(int i);
int				ft_printf(const char *string, ...);
int				print_cnv(const char *string, va_list arg,
				int *cursor, t_flags flags);
char			detect_cnv_exist(const char *string);
int				ft_numbersize(unsigned long long number);
void			ft_assigntypeu(va_list arg, unsigned long long *number, t_flags flags);
//int				ft_numbersize(int number);
void			ft_printnumberbin(va_list arg, int *cursor, t_flags flags);
void			ft_printnumber(va_list arg, int *cursor, t_flags flags);
void			ft_printnumberu(va_list arg, int *cursor, t_flags flags);
void			ft_printnumberhexmin(va_list arg, int *cursor, t_flags flags);
void			ft_printnumberhexmaj(va_list arg, int *cursor, t_flags flags);
void			ft_printnumberoct(va_list arg, int *cursor, t_flags flags);
void			ft_printadresse(va_list arg, int *cursor, t_flags flags);
void			ft_printstring(va_list arg, int *cursor, t_flags flags);
void			ft_printchar(va_list arg, int *cursor, t_flags flags);
void			ft_printpercent(int *cursor, t_flags flags);
void			ft_hashprint(int **cursor, unsigned char type, t_flags flags);
void			ft_initflags(t_flags *flags);
void			ft_printflags(t_flags flags);
void			ft_printfloat(va_list arg, int *cursor, t_flags flags);
void			ft_assignflag(va_list arg, t_flags *flags, char **string);
char			*detect_flg(char *string, va_list arg, int *cursor,
				t_flags *flags);

#endif
