/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:18:05 by eelroy            #+#    #+#             */
/*   Updated: 2021/12/07 14:10:53 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	ft_full_space_zero(char ok, char space_zero, int wid)
{
	int		i;
	char	*s;

	if (!ok)
		return (0);
	if (wid < 1)
		return (1);
	s = (char *)malloc(sizeof(char) * wid);
	if (!s)
		return (0);
	if (space_zero != 0)
		space_zero = ' ';
	else
		space_zero = '0';
	i = -1;
	while (i++ < wid - 1)
		s[i] = space_zero;
	write(1, s, i);
	free(s);
	return (1);
}

int	ft_print_c(t_data *d, char c, int *res)
{
	int		ok;

	if (d->width < 2)
		d->width = 1;
	if (d->width < 2 || d->flags % 3 == 0)
		write(1, &c, 1);
	ok = ft_full_space_zero(1, d->flags % 11, d->width - 1);
	if (!ok)
		return (0);
	if (d->flags % 3 != 0 && d->width > 1)
		write(1, &c, 1);
	*res += d->width;
	return (1);
}

int	ft_print_s(t_data *d, va_list args, int *res)
{
	int		len_str;
	int		ok;
	char	*s;

	s = va_arg(args, char *);
	if (s == 0)
		s = "(null)";
	len_str = ft_strlen(s);
	if (d->flags % 17 == 0 && len_str > d->prec)
		len_str = d->prec;
	if (d->width < len_str)
		d->width = len_str;
	if (len_str >= d->width || d->flags % 3 == 0)
		write(1, s, len_str);
	ok = ft_full_space_zero(1, d->flags % 11, d->width - len_str);
	if (!ok)
		return (0);
	if (d->flags % 3 != 0 && len_str < d->width)
		write(1, s, len_str);
	*res += d->width;
	return (1);
}
