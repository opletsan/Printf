/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_str_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 22:38:53 by opletsan          #+#    #+#             */
/*   Updated: 2018/08/17 22:38:56 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		ft_strlen(unsigned char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static inline int	ft_unilen(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x1FFFFF)
		return (4);
	return (0);
}

void				use_flag_char(t_prnt *s, wchar_t c)
{
	int	len;

	len = 1;
	if (s->fsize == 3)
		len = ft_unilen(c);
	s->width -= len;
	if (!s->fzero && !s->fminus)
		print_width_prec(s, 'w', ' ');
	if (s->fzero)
		print_width_prec(s, 'w', '0');
	print_unicode(s, c, len);
	if (s->fminus)
		print_width_prec(s, 'w', ' ');
}

void				use_flag_str(t_prnt *s, unsigned char *str, intmax_t len)
{
	if (!str)
		str = (unsigned char*)"(null)";
	len = ft_strlen(str);
	if (s->prec <= len && s->prec > -1)
	{
		len = s->prec;
		s->prec = 0;
	}
	s->width -= len;
	if (!s->fzero && !s->fminus)
		print_width_prec(s, 'w', ' ');
	else if (s->fzero)
		print_width_prec(s, 'w', '0');
	print_str(s, str, len);
	if (s->fminus)
		print_width_prec(s, 'w', ' ');
}

void				use_flag_unistr(t_prnt *s, wchar_t *str, intmax_t len)
{
	wchar_t	*tmp;

	tmp = str--;
	while (*tmp)
	{
		len += ft_unilen(*tmp);
		if (len > s->prec && s->prec > -1)
		{
			len -= ft_unilen(*tmp);
			break ;
		}
		tmp++;
	}
	s->width -= len;
	if (!s->fzero && !s->fminus)
		print_width_prec(s, 'w', ' ');
	else if (s->fzero)
		print_width_prec(s, 'w', '0');
	if (s->i + len >= BUFF_SIZE)
		print_buf(s);
	while (++str < tmp)
		print_unicode(s, *str, ft_unilen(*str));
	if (s->fminus)
		print_width_prec(s, 'w', ' ');
}
