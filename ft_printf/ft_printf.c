/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:39:38 by eelroy            #+#    #+#             */
/*   Updated: 2021/12/07 11:31:44 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_just_str(int *res, char *s)
{
	char	*just_str;
	size_t	size;
	size_t	i;

	size = 0;
	while (s[size] && s[size] != '%')
		size++;
	if (!size)
		return (s);
	just_str = (char *)malloc(sizeof(char) * size);
	if (!just_str)
		return (0);
	i = 0;
	while (i < size)
	{
		just_str[i] = s[i];
		i++;
	}
	write(1, just_str, size);
	free(just_str);
	*res += (int) size;
	return (s + i);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	char	*s;
	int		res;

	if (!str || str[0] == 0)
		return (0);
	va_start(args, str);
	s = (char *)str;
	res = 0;
	while (s && *s)
	{
		s = ft_just_str(&res, s);
		s = ft_with_specifier(&res, s, args);
	}
	va_end(args);
	if (!s)
		return (0);
	return (res);
}
