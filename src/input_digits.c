/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 22:45:09 by opletsan          #+#    #+#             */
/*   Updated: 2018/08/17 22:45:11 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_num_len(uintmax_t n, int base)
{
	int	len;

	len = 1;
	while (n /= base)
		len++;
	return (len);
}

static inline void	use_flag_digits(t_prnt *s, uintmax_t n, int len, int base)
{
	len += (s->fapos && (base == 10 || base == 8)) ? (len - 1) / 3 : 0;
	len += (s->fapos && base == 2) ? (len - 1) / 4 : 0;
	len += (!s->fapos && s->fsharp == 1 && base == 2) ? (len - 1) / 8 : 0;
	s->fbase *= (s->fsharp && s->fbase == 8 && ((!len && !n) ||
		(s->prec <= len && n))) ? (-1) : 1;
	s->width -= ((base == 16 && s->fsharp == 2) || ((s->f || (!s->f &&
		s->fplus) || (s->fspace && !s->f)) && base == 10) ||
		(s->fsharp == 1 && (s->fbase == -8 || (base == 16 && n))));
	s->width -= (base == 16 && ((s->fsharp == 1 && n) || s->fsharp == 2));
	s->prec *= (s->prec != -1 && ((s->prec -= len) < 0)) ? 0 : 1;
	s->width -= len;
	if (s->width > s->prec && !s->fminus &&
		(s->prec > -1 || (s->prec == -1 && !s->fzero)))
	{
		s->width -= (s->prec == -1) ? 0 : s->prec;
		print_width_prec(s, 'w', ' ');
	}
	print_sign(s, n, len);
	if (s->fzero && s->prec == -1)
		print_width_prec(s, 'w', '0');
	s->width -= (s->prec == -1) ? 0 : s->prec;
	print_width_prec(s, 'p', '0');
	len ? itoa_uintmax(s, n, ft_num_len(n, base), base) : 0;
	if (s->width > s->prec && s->fminus)
		print_width_prec(s, 'w', ' ');
}

void				digits_di(t_prnt *s, char spec, intmax_t tmp)
{
	if (s->fsize == 7 || s->fsize == 6)
		tmp = va_arg(s->ap, ssize_t);
	else if (s->fsize == 5)
		tmp = va_arg(s->ap, intmax_t);
	else if (s->fsize == 4)
		tmp = va_arg(s->ap, long long int);
	else if (s->fsize == 3 || spec == 'D')
		tmp = va_arg(s->ap, long int);
	else if (s->fsize == 0)
		tmp = va_arg(s->ap, int);
	else if (s->fsize == 2)
		tmp = (short)va_arg(s->ap, int);
	else if (s->fsize == 1)
		tmp = (signed char)va_arg(s->ap, int);
	if (s->prec == 0 && tmp == 0)
		use_flag_digits(s, tmp, 0, 0);
	else if (tmp < 0)
	{
		s->f = 1;
		use_flag_digits(s, (tmp * (-1)), ft_num_len(tmp * (-1), 10), 10);
	}
	else
		use_flag_digits(s, tmp, ft_num_len(tmp, 10), 10);
}

void				digits_puox(t_prnt *s, char spec, uintmax_t tmp, int base)
{
	if (spec == 'X' || spec == 'B')
		(s->fbase = -base);
	else
		(s->fbase = base);
	if (s->fsize == 7 || s->fsize == 6)
		tmp = va_arg(s->ap, size_t);
	else if (s->fsize == 5 || spec == 'p')
		tmp = va_arg(s->ap, uintmax_t);
	else if (s->fsize == 4)
		tmp = va_arg(s->ap, unsigned long long int);
	else if (s->fsize == 3 || spec == 'O' || spec == 'U')
		tmp = va_arg(s->ap, unsigned long int);
	else if (s->fsize == 0)
		tmp = va_arg(s->ap, unsigned int);
	else if (s->fsize == 2)
		tmp = (unsigned short)va_arg(s->ap, unsigned int);
	else if (s->fsize == 1)
		tmp = (unsigned char)va_arg(s->ap, unsigned int);
	s->fplus = 0;
	s->fspace = 0;
	if (!s->prec && !tmp)
		use_flag_digits(s, tmp, 0, base);
	else
		use_flag_digits(s, tmp, ft_num_len(tmp, base), base);
}
