/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_printable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:37:22 by opletsan          #+#    #+#             */
/*   Updated: 2018/09/01 16:37:25 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_nonprnt_char(t_prnt *s, unsigned char c, int len)
{
	if (s->i + len >= BUFF_SIZE)
		print_buf(s);
	if (len > 1)
		s->ret -= len - 1;
	if (len == 2)
	{
		s->buf[s->i++] = '^';
		if (c == 127)
			s->buf[s->i++] = c - 64;
		else
			s->buf[s->i++] = c + 64;
	}
	else if (len == 4)
	{
		s->buf[s->i++] = 'M';
		s->buf[s->i++] = '-';
		s->buf[s->i++] = '^';
		s->buf[s->i++] = c - 64;
	}
	else
		s->buf[s->i++] = c;
}

void	use_flag_nonprnt_char(t_prnt *s, unsigned char c)
{
	int	len;

	len = 1;
	if (c <= 31 || c == 127)
		len = 2;
	else if (c >= 128 && c <= 159)
		len = 4;
	s->width -= 1;
	if (!s->fzero && !s->fminus)
		print_width_prec(s, 'w', ' ');
	if (s->fzero)
		print_width_prec(s, 'w', '0');
	print_nonprnt_char(s, c, len);
	if (s->fminus)
		print_width_prec(s, 'w', ' ');
}
