/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:37:06 by eelroy            #+#    #+#             */
/*   Updated: 2021/12/07 14:11:03 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_switch(t_data *d, char *s, va_list args, int *res)
{
	long int			var;
	unsigned long int	var2;

	d->type = *s;
	if (*s == 'c' || *s == 'd' || *s == 'i')
		var = va_arg(args, int);
	else if (*s == 'u')
		var = va_arg(args, unsigned int);
	else if (*s == 'p')
		var2 = va_arg(args, unsigned long int);
	else if (*s == 'x' || *s == 'X')
		var2 = va_arg(args, unsigned int);
	if (*s == '%')
		var = ft_print_c(d, '%', res);
	else if (*s == 'c')
		var = ft_print_c(d, var, res);
	else if (*s == 's')
		var = ft_print_s(d, args, res);
	else if (*s == 'd' || *s == 'i' || *s == 'u')
		var = ft_print_d(d, var, res);
	else if (*s == 'x' || *s == 'X' || *s == 'p')
		var = ft_print_x(d, var2, res);
	if (!var && !var2)
		return (0);
	return (s + 1);
}

static char	*ft_flags(t_data *d, char *s, int fl)
{
	char	*s1;

	s1 = "Xxuidpsc%123456789.";
	if (fl == 1)
		s1 = "Xxuidpsc%";
	while (s && *s && !(ft_strchr(s1, *s)))
	{
		if (*s == '#' && d->flags % 2)
			d->flags *= 2;
		if (*s == '-' && d->flags % 3)
			d->flags *= 3;
		if (*s == '+' && d->flags % 5)
			d->flags *= 5;
		if (*s == ' ' && d->flags % 7)
			d->flags *= 7;
		if (*s == '0' && d->flags % 11)
			d->flags *= 11;
		s++;
	}
	return (s);
}

static char	*ft_width_prec(t_data *d, char *s)
{
	if (!(ft_isdigit(*s)) && *s != '.')
		return (s);
	d->width = ft_atoi(s);
	if (d->width > 0)
		d->flags *= 13;
	while (ft_isdigit(*s))
		s++;
	if (*s != '.')
		return (s);
	d->prec = 0;
	s++;
	if (ft_isdigit(*s))
		d->prec = ft_atoi(s);
	if (d->prec >= 0)
		d->flags *= 17;
	while (ft_isdigit(*s))
		s++;
	return (s);
}

char	*ft_with_specifier(int *res, char *s, va_list args)
{
	t_data	*d;

	if (s == 0 || *s == 0)
		return (s);
	s++;
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (0);
	d->flags = 1;
	d->width = -1;
	d->prec = -1;
	d->ok = 1;
	s = ft_flags(d, s, 0);
	s = ft_width_prec(d, s);
	s = ft_flags(d, s, 1);
	if (!s || !*s)
		return (0);
	if (!(d->flags % 5) && !(d->flags % 7))
		d->flags /= 7;
	if (!(d->flags % 11) && !(d->flags % 3))
		d->flags /= 11;
	s = ft_switch(d, s, args, res);
	free(d);
	return (s);
}
