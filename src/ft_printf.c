/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:57:29 by opletsan          #+#    #+#             */
/*   Updated: 2018/07/24 13:57:32 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void	flag_default(t_prnt *s)
{
	s->f = 0;
	s->fr = 0;
	s->fbase = 10;
	s->fsize = 0;
	s->fzero = 0;
	s->fsharp = 0;
	s->fspace = 0;
	s->fminus = 0;
	s->fplus = 0;
	s->fapos = 0;
	s->prec = -1;
	s->width = 0;
	s->fdol = 0;
}

static inline void	start_finish_init(t_prnt *s, int fd, va_list ap, char flag)
{
	if (flag == 's')
	{
		s->i = 0;
		s->ret = 0;
		s->fd = fd;
		s->tcol = NULL;
		s->bcol = NULL;
		va_copy(s->ap, ap);
		va_copy(s->begin, s->ap);
	}
	else if (flag == 'f')
	{
		if (s->tcol || s->bcol)
			valid_color(s, "CEOC}end");
		print_buf(s);
		va_end(s->begin);
		va_end(s->ap);
	}
}

int					ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_prnt	s;

	if (!format || write(fd, s.buf, 0) < 0)
		return (-1);
	start_finish_init(&s, fd, ap, 's');
	while (*format)
	{
		if (*format == '%')
		{
			flag_default(&s);
			format = src_flag(&s, ++format);
		}
		else if (*format == '{')
			format = valid_color(&s, ++format);
		else if ((s.tcol || s.bcol) && *format == '\n')
			format = print_else(&s, format);
		else
		{
			if (s.i == BUFF_SIZE)
				print_buf(&s);
			s.buf[s.i++] = *format++;
		}
	}
	start_finish_init(&s, fd, ap, 'f');
	return (s.ret);
}

int					ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	if (!format)
		return (-1);
	va_start(ap, format);
	ret = ft_vdprintf(1, format, ap);
	va_end(ap);
	return (ret);
}

int					ft_dprintf(int fd, const char *format, ...)
{
	t_prnt	s;
	va_list	ap;
	int		ret;

	if (!format || write(fd, s.buf, 0) < 0)
		return (-1);
	va_start(ap, format);
	ret = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}
