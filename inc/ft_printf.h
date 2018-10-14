/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:58:04 by opletsan          #+#    #+#             */
/*   Updated: 2018/07/24 14:01:34 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <locale.h>
# include <time.h>

# define BUFF_SIZE 3072

# define CEOC  "\x1B[00m"

# define TBLC  "\x1B[30m"
# define TRED  "\x1B[31m"
# define TGRN  "\x1B[32m"
# define TYEL  "\x1B[33m"
# define TBLU  "\x1B[34m"
# define TMAG  "\x1B[35m"
# define TCYN  "\x1B[36m"
# define TWHT  "\x1B[37m"

# define BBLC  "\x1B[40m"
# define BRED  "\x1B[41m"
# define BGRN  "\x1B[42m"
# define BYEL  "\x1B[43m"
# define BBLU  "\x1B[44m"
# define BMAG  "\x1B[45m"
# define BCYN  "\x1B[46m"
# define BWHT  "\x1B[47m"

# define C_CEOC  0x434F4543

# define C_TBLC  0x434C4254
# define C_TRED  0x44455254
# define C_TGRN  0x4E524754
# define C_TYEL  0x4C455954
# define C_TBLU  0x554C4254
# define C_TMAG  0x47414D54
# define C_TCYN  0x4E594354
# define C_TWHT  0x54485754

# define C_BBLC  0x434C4242
# define C_BRED  0x44455242
# define C_BGRN  0x4E524742
# define C_BYEL  0x4C455942
# define C_BBLU  0x554C4242
# define C_BMAG  0x47414D42
# define C_BCYN  0x4E594342
# define C_BWHT  0x54485742

typedef struct		s_prnt
{
	char			buf[BUFF_SIZE];
	int				fd;
	va_list			ap;
	va_list			begin;
	char			*tcol;
	char			*bcol;
	intmax_t		i;
	intmax_t		ret;
	int				width;
	int				prec;
	int				fdol;
	int				fsize;
	int				fbase;
	unsigned int	f:1;
	unsigned int	fr:1;
	unsigned int	fzero:1;
	unsigned int	fsharp:2;
	unsigned int	fspace:1;
	unsigned int	fminus:1;
	unsigned int	fplus:1;
	unsigned int	fapos:1;
}					t_prnt;

void				print_nonprnt_char(t_prnt *s, unsigned char c, int len);
void				use_flag_nonprnt_char(t_prnt *s, unsigned char c);
int					ft_num_len(uintmax_t n, int base);
void				print_str(t_prnt *s, unsigned char *str, intmax_t len);
void				print_buf(t_prnt *s);
void				itoa_uintmax(t_prnt *s, uintmax_t n, int len, int base);
void				src_arg(t_prnt *s, int arg);
const char			*width(t_prnt *s, const char *str);
const char			*precision(t_prnt *s, const char *str);
const char			*size(t_prnt *s, const char *str);
void				print_sign(t_prnt *s, uintmax_t n, int len);
void				print_width_prec(t_prnt *s, char f, char c);
void				digits_di(t_prnt *s, char spec, intmax_t tmp);
void				digits_puox(t_prnt *s, char spec, uintmax_t tmp, int base);
void				print_unicode(t_prnt *s, wchar_t c, int len);
void				use_flag_char(t_prnt *s, wchar_t c);
void				use_flag_str(t_prnt *s, unsigned char *str, intmax_t len);
void				use_flag_unistr(t_prnt *s, wchar_t *str, intmax_t len);
const char			*src_flag(t_prnt *s, const char *str);
const char			*valid_color(t_prnt *s, const char *str);
const char			*print_else(t_prnt *s, const char *str);
int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_vdprintf(int fd, const char *format, va_list ap);

#endif
