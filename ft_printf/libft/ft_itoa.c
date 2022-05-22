/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:03:55 by eelroy            #+#    #+#             */
/*   Updated: 2021/12/07 13:24:29 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_num_str(char *str, long int n, int *len)
{
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	if (n < 0)
		sign = -1;
	while (n / 10)
	{
		str[i] = n % 10 * sign + '0';
		i++;
		n /= 10;
	}
	str[i] = n * sign + '0';
	str[i + 1] = 0;
	*len = i + 1;
	return (str);
}

char	*ft_opt_itoa(long int n, int *len, int prec)
{
	int		len_s1;
	int		i;
	char	*str;
	char	tmp[20];
	char	*res;

	len_s1 = 0;
	str = ft_num_str(tmp, n, &len_s1);
	if (prec == 0 && n == 0)
		len_s1 = 0;
	res = (char *)malloc(sizeof(char) * (len_s1 + 1));
	if (!res)
		return (0);
	i = 0;
	while (i < len_s1)
	{
		res[i] = str[len_s1 - i - 1];
		i++;
	}
	res[i] = 0;
	*len = i;
	return (res);
}
