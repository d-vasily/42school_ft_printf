/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:00:20 by eelroy            #+#    #+#             */
/*   Updated: 2021/12/07 14:10:24 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "./libft/libft.h"
# include <stdarg.h>

typedef struct d_data
{
	int		flags;
	int		width;
	int		prec;
	char	type;
	char	sign[2];
	char	len_sign;
	char	ok;

}	t_data;

int		ft_printf(const char *str, ...);
char	ft_full_space_zero(char ok, char space_zero, int wid);
int		ft_print_c(t_data *d, char c, int *res);
int		ft_print_s(t_data *d, va_list args, int *res);
int		ft_print_x(t_data *d, unsigned long int num, int *res);
int		ft_print_d(t_data *d, long int num, int *res);
char	*ft_with_specifier(int *res, char *s, va_list args);

#endif
