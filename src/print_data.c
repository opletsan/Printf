/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 22:25:20 by opletsan          #+#    #+#             */
/*   Updated: 2018/08/17 22:25:22 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_str(t_prnt *s, unsigned char *str, intmax_t len)
{
	if (s->i + len >= BUFF_SIZE)
		print_buf(s);
	while (len > 0)
	{
		s->buf[s->i++] = *str++;
		len--;
	}
}

void	itoa_uintmax(t_prnt *s, uintmax_t n, int len, int base)
{
	int			tmp;
	uintmax_t	l;

	l = 1;
	tmp = len;
	while (--tmp)
		l *= base;
	while (len--)
	{
		if (s->i + 2 >= BUFF_SIZE)
			print_buf(s);
		s->buf[s->i++] = (s->fbase == -16) ? "0123456789ABCDEF"[n / l] :
											"0123456789abcdef"[n / l];
		if (len > 1 && ((s->fapos == 1 && (((base == 10 || base == 8) &&
				len % 3 == 0) || (base == 2 && len % 4 == 0))) ||
				(s->fsharp == 1 && base == 2 && len % 8 == 0)))
			s->buf[s->i++] = (s->fsharp == 1 && base == 2 && len % 8 == 0 &&
							len > 1) ? '|' : ' ';
		n %= l;
		l /= base;
	}
}

void	print_unicode(t_prnt *s, wchar_t c, int len)
{
	if (s->i + 4 == BUFF_SIZE)
		print_buf(s);
	if (len == 1 || MB_CUR_MAX == 1)
		s->buf[s->i++] = (char)c;
	else if (len == 2)
	{
		s->buf[s->i++] = (49280 >> 8) | ((c & 0xFC0) >> 6);
		s->buf[s->i++] = 49280 | (c & 0x3F);
	}
	else if (len == 3)
	{
		s->buf[s->i++] = (14712960 >> 16) | ((c & 0xF000) >> 12);
		s->buf[s->i++] = (14712960 >> 8) | ((c & 0xFC0) >> 6);
		s->buf[s->i++] = 14712960 | (c & 0x3F);
	}
	else if (len == 4)
	{
		s->buf[s->i++] = (4034953344 >> 24) | ((c & 0xF000) >> 18);
		s->buf[s->i++] = (4034953344 >> 16) | ((c & 0x3F000) >> 12);
		s->buf[s->i++] = (4034953344 >> 8) | ((c & 0xFC0) >> 6);
		s->buf[s->i++] = 4034953344 | (c & 0x3F);
	}
}

void	print_sign(t_prnt *s, uintmax_t n, int len)
{
	if (s->i + 2 >= BUFF_SIZE)
		print_buf(s);
	if (s->f == 1 && s->fbase == 10)
		s->buf[s->i++] = '-';
	else if (s->fplus == 1 && s->f == 0 && s->fbase == 10)
		s->buf[s->i++] = '+';
	else if (s->fspace == 1 && s->f == 0 && s->fbase == 10)
		s->buf[s->i++] = ' ';
	else if ((s->fsharp == 1 && (s->fbase == -8 || ((s->fbase == -16 ||
			s->fbase == 16) && n != 0))) || (s->fsharp == 2 && s->fbase == 16))
		s->buf[s->i++] = '0';
	else if (s->fbase == -2 && ((ft_numlen(n, -s->fbase)) % 4 != 0) && len > 0)
	{
		len = ft_numlen(n, -s->fbase);
		while (len++ % 4)
		{
			if (s->i == BUFF_SIZE)
				print_buf(s);
			s->buf[s->i++] = '0';
			s->prec--;
		}
	}
	if ((s->fbase == 16 || s->fbase == -16) && ((s->fsharp == 1 && n != 0) ||
			s->fsharp == 2))
		s->buf[s->i++] = (s->fbase == 16) ? 'x' : 'X';
}

void	print_width_prec(t_prnt *s, char f, char c)
{
	while (s->width > 0 && f == 'w')
	{
		if (s->i == BUFF_SIZE)
			print_buf(s);
		s->buf[s->i++] = c;
		s->width--;
	}
	while (s->prec > 0 && f == 'p')
	{
		if (s->i == BUFF_SIZE)
			print_buf(s);
		s->buf[s->i++] = c;
		s->prec--;
	}
}
