/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_flag_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 22:21:55 by opletsan          #+#    #+#             */
/*   Updated: 2018/08/17 22:21:57 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void						src_arg(t_prnt *s, int arg)
{
	if (arg != 0)
		va_copy(s->ap, s->begin);
	while (--arg > 0)
		va_arg(s->ap, int);
}

static inline void			check_flag(t_prnt *s, char flag)
{
	if (flag == '-')
	{
		s->fminus = 1;
		s->fzero = 0;
	}
	else if (flag == '+')
	{
		s->fplus = 1;
		s->fspace = 0;
	}
	else if (flag == ' ' && s->fplus == 0)
		s->fspace = 1;
	else if (flag == '0' && s->fminus == 0)
		s->fzero = 1;
	else if (flag == '#')
		s->fsharp = 1;
	else if (flag == '\'')
		s->fapos = 1;
	else if (flag == 'r')
		s->fr = 1;
}

static inline void			src_spec_c_s(t_prnt *s, char spec)
{
	wchar_t			*str;
	const time_t	timer = time(NULL);

	if (spec == 'C')
		s->fsize = 3;
	if (spec == 'c' || spec == 'C')
	{
		(s->fr == 1) ?
			use_flag_nonprnt_char(s, (unsigned char)va_arg(s->ap, int)) :
			use_flag_char(s, (wchar_t)va_arg(s->ap, int));
	}
	else if ((spec == 's' && s->fsize == 3) || spec == 'S')
	{
		(!(str = (wchar_t*)va_arg(s->ap, intmax_t))) ?
			use_flag_str(s, NULL, 0) : use_flag_unistr(s, str, 0);
	}
	else if (spec == 's')
		use_flag_str(s, (unsigned char*)va_arg(s->ap, unsigned char*), 0);
	else if (spec == 'k')
	{
		use_flag_str(s, (unsigned char*)ctime(&timer), 0);
		s->buf[--s->i] = '\0';
		s->i++;
	}
}

static inline const char	*src_spec(t_prnt *s, const char *str, intmax_t *n)
{
	src_arg(s, s->fdol);
	if (*str == 'c' || *str == 'C' || *str == 's' || *str == 'S' ||
			*str == 'k')
		src_spec_c_s(s, *str);
	else if (*str == 'd' || *str == 'i' || *str == 'D')
		digits_di(s, *str, 0);
	else if (*str == 'u' || *str == 'U')
		digits_puox(s, *str, 0, 10);
	else if (*str == 'x' || *str == 'X' || *str == 'p')
	{
		if (*str == 'p')
			s->fsharp = 2;
		digits_puox(s, *str, 0, 16);
	}
	else if (*str == 'o' || *str == 'O')
		digits_puox(s, *str, 0, 8);
	else if (*str == 'b' || *str == 'B')
		digits_puox(s, *str, 0, 2);
	else if (*str == 'n')
	{
		if (!(n = va_arg(s->ap, intmax_t*)))
			return (++str);
		*n = s->ret + s->i;
	}
	return (++str);
}

const char					*src_flag(t_prnt *s, const char *str)
{
	while (*str)
	{
		if (*str == '0' || *str == '#' || *str == ' ' || *str == '-' ||
	*str == '+' || *str == '\'' || *str == '$' || *str == 'r')
			check_flag(s, *str++);
		else if (*str == '*' || (*str >= '0' && *str <= '9'))
			str = width(s, str);
		else if (*str == '.')
			str = precision(s, ++str);
		else if (*str == 'h' || *str == 'l' || *str == 'j' || *str == 't'
				|| *str == 'z' || *str == 'q')
			str = size(s, str);
		else if (*str == 'n' || *str == 'd' || *str == 'i' || *str == 'D' ||
	*str == 'u' || *str == 'U' || *str == 'c' || *str == 'C' || *str == 's'
	|| *str == 'S' || *str == 'x' || *str == 'X' || *str == 'o' || *str == 'O'
	|| *str == 'b' || *str == 'B' || *str == 'p' || *str == 'k')
			return (src_spec(s, str, NULL));
		else
		{
			use_flag_char(s, *str++);
			break ;
		}
	}
	return (str);
}
