/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 22:17:50 by opletsan          #+#    #+#             */
/*   Updated: 2018/08/17 22:17:54 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					print_buf(t_prnt *s)
{
	write(s->fd, s->buf, s->i);
	s->ret += s->i;
	s->i = 0;
}

static inline size_t	*check_color2(t_prnt *s, int *dec)
{
	if (*dec == C_CEOC)
	{
		s->tcol = NULL;
		s->bcol = NULL;
		return ((size_t*)CEOC);
	}
	else if (*dec == C_BBLC)
		return ((size_t*)BBLC);
	else if (*dec == C_BRED)
		return ((size_t*)BRED);
	else if (*dec == C_BGRN)
		return ((size_t*)BGRN);
	else if (*dec == C_BYEL)
		return ((size_t*)BYEL);
	else if (*dec == C_BBLU)
		return ((size_t*)BBLU);
	else if (*dec == C_BMAG)
		return ((size_t*)BMAG);
	else if (*dec == C_BCYN)
		return ((size_t*)BCYN);
	else if (*dec == C_BWHT)
		return ((size_t*)BWHT);
	return (0);
}

static inline int		check_color1(t_prnt *s, int *dec)
{
	size_t	*b;
	size_t	*a;

	a = (size_t*)&s->buf[s->i];
	if (*dec == C_TBLC)
		b = (size_t*)TBLC;
	else if (*dec == C_TRED)
		b = (size_t*)TRED;
	else if (*dec == C_TGRN)
		b = (size_t*)TGRN;
	else if (*dec == C_TYEL)
		b = (size_t*)TYEL;
	else if (*dec == C_TBLU)
		b = (size_t*)TBLU;
	else if (*dec == C_TMAG)
		b = (size_t*)TMAG;
	else if (*dec == C_TCYN)
		b = (size_t*)TCYN;
	else if (*dec == C_TWHT)
		b = (size_t*)TWHT;
	else if (!(b = check_color2(s, dec)))
		return (0);
	*a = *b;
	return (1);
}

const char				*valid_color(t_prnt *s, const char *str)
{
	int	i;

	i = 0;
	while (*(str + i) && *(str + i) != '}')
		i++;
	if (s->i + 8 >= BUFF_SIZE)
		print_buf(s);
	if (i != 4 || *(str + i) != '}' ||
			!check_color1(s, (int*)(str)))
	{
		s->buf[s->i++] = *(str - 1);
		return (str);
	}
	if (*str == 'B')
		s->bcol = (char*)str;
	else if (*str == 'T')
		s->tcol = (char*)str;
	s->i += 6;
	s->ret -= 6;
	return (str + i + 1);
}

const char				*print_else(t_prnt *s, const char *str)
{
	if (s->i + 19 >= BUFF_SIZE)
		print_buf(s);
	*(size_t*)&s->buf[s->i] = *(size_t*)CEOC;
	s->i += 6;
	s->ret -= 6;
	s->buf[s->i++] = *str++;
	if (s->tcol && check_color1(s, (int*)s->tcol))
	{
		s->i += 6;
		s->ret -= 6;
	}
	if (s->bcol && check_color1(s, (int*)s->bcol))
	{
		s->i += 6;
		s->ret -= 6;
	}
	return (str);
}
