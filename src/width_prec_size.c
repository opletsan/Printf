/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_prec_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 22:47:50 by opletsan          #+#    #+#             */
/*   Updated: 2018/08/17 22:47:52 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline int	check_minus(t_prnt *s, int ret, int i)
{
	if (ret < 0 && i == 1)
	{
		ret *= -1;
		s->fminus = 1;
		s->fzero = 0;
	}
	else if (ret < 0 && i == 0)
		ret = -1;
	return (ret);
}

static inline int	star(t_prnt *s, const char **str, int ret, int i)
{
	static va_list	aptmp;

	if (**str <= '0' || **str >= '9')
		return (check_minus(s, va_arg(s->ap, int), i));
	while (**str >= '0' && **str <= '9')
		ret = ret * 10 + (*(*str)++ - '0');
	if (**str != '$' && i == 1)
	{
		s->fdol = 2;
		return (ret);
	}
	if (**str == '$')
	{
		va_copy(aptmp, s->ap);
		src_arg(s, ret);
		ret = va_arg(s->ap, int);
		va_copy(s->ap, aptmp);
		va_end(aptmp);
	}
	return (check_minus(s, ret, i));
}

const char			*width(t_prnt *s, const char *str)
{
	int		tmp;

	tmp = s->width;
	if (*str >= '0' && *str <= '9')
	{
		s->width = 0;
		while (*str >= '0' && *str <= '9')
			s->width = s->width * 10 + (*str++ - '0');
		if (*str == '$' && s->width != 0)
		{
			s->fdol = s->width;
			s->width = 0;
			str++;
		}
	}
	if (*str == '*')
		if (*(++str) != '$')
			s->width = star(s, &str, 0, 1);
	if (s->width == 0)
		s->width = tmp;
	return (str);
}

const char			*precision(t_prnt *s, const char *str)
{
	s->prec = 0;
	while (*str >= '0' && *str <= '9')
		s->prec = s->prec * 10 + (*str++ - '0');
	if (*str == '*' && s->prec == 0)
		if (*(++str) != '$')
			s->prec = star(s, &str, 0, 0);
	return (str);
}

const char			*size(t_prnt *s, const char *str)
{
	if (*str == 'h' && s->fsize == 2)
		s->fsize = 1;
	else if (*str == 'h' && s->fsize <= 1)
		s->fsize = 2;
	else if (*str == 'q' || (*str == 'l' && s->fsize == 3))
		s->fsize = 4;
	else if (*str == 'l' && (s->fsize == 4 || s->fsize < 3))
		s->fsize = 3;
	else if (*str == 'j' && s->fsize < 5)
		s->fsize = 5;
	else if (*str == 't' && s->fsize < 6)
		s->fsize = 6;
	else if (*str == 'z' && s->fsize < 7)
		s->fsize = 7;
	return (++str);
}
