/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nums.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:01:28 by eelroy            #+#    #+#             */
/*   Updated: 2021/12/07 14:10:41 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_convert(unsigned long int num, \
			char type, int *len_str, const char *x)
{
	char	tmp[22];
	char	*res;
	int		i;
	int		j;

	if (type == 'X')
		x = "0123456789ABCDEF";
	i = 0;
	while (num / 16)
	{
		tmp[i++] = x[num % 16];
		num /= 16;
	}
	tmp[i++] = x[num];
	res = (char *) malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	j = -1;
	while (j++ < i - 1)
		res[j] = tmp[i - j - 1];
	res[j] = 0;
	*len_str = j;
	return (res);
}

static char	*ft_get_sign(long int num, t_data *d, char *s)
{
	if (!s)
		return (0);
	d->sign[0] = '0';
	d->sign[1] = 'x';
	d->len_sign = 0;
	if (d->type == 'p')
		d->len_sign = 2;
	if ((d->type == 'x' || d->type == 'X') && *s != '0')
		d->len_sign = 2 * (d->flags % 2 == 0);
	if (d->type == 'X')
		d->sign[1] = 'X';
	if (d->type == 'x' || d->type == 'X' || d->type == 'p')
		return (s);
	d->sign[0] = 0;
	if (num < 0)
		d->sign[0] = '-';
	else if (d->flags % 5 == 0)
		d->sign[0] = '+';
	else if (d->flags % 7 == 0)
		d->sign[0] = ' ';
	if (d->sign[0] != 0)
		d->len_sign = 1;
	return (s);
}

int	ft_print_d(t_data *d, long int num, int *res)
{
	char	*s;
	int		len_str;

	s = ft_opt_itoa(num, &len_str, d->prec);
	s = ft_get_sign(num, d, s);
	if (!s)
		return (0);
	if (d->prec < len_str)
		d->prec = len_str;
	if (d->width < d->prec + d->len_sign)
		d->width = d->prec + d->len_sign;
	d->width = d->width - d->prec - d->len_sign;
	if (d->flags % 11 == 0)
		write(1, d->sign, d->len_sign);
	if (d->flags % 3 != 0)
		d->ok = ft_full_space_zero(1, d->flags % 11, d->width);
	if (d->flags % 11 != 0)
		write(1, d->sign, d->len_sign);
	d->ok = ft_full_space_zero(d->ok, 0, d->prec - len_str);
	write(1, s, len_str);
	if (d->flags % 3 == 0)
		d->ok = ft_full_space_zero(d->ok, 1, d->width);
	free(s);
	*res += d->width + d->prec + d->len_sign;
	return (d->ok);
}

int	ft_print_x(t_data *d, unsigned long int num, int *res)
{
	char	*s;
	int		len_str;
	char	ok;

	ok = 1;
	s = ft_convert(num, d->type, &len_str, "0123456789abcdef");
	s = ft_get_sign(1, d, s);
	if (!s)
		return (0);
	if (d->prec < len_str)
		d->prec = len_str;
	if (d->width < d->prec + d->len_sign)
		d->width = d->prec + d->len_sign;
	else if (d->flags % 3 != 0)
		ok = ft_full_space_zero(ok, 0, d->width - d->prec - d->len_sign);
	if (d->len_sign == 2)
		write(1, d->sign, 2);
	ok = ft_full_space_zero(ok, 0, d->prec - len_str);
	write(1, s, len_str);
	if (d->flags % 3 == 0)
		ok = ft_full_space_zero(ok, 1, d->width - d->prec - d->len_sign);
	free(s);
	*res += d->width;
	return (ok);
}
