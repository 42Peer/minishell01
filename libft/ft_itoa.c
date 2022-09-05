/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:59:44 by sumsong           #+#    #+#             */
/*   Updated: 2022/01/25 00:24:00 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_positive(int n);
static int	ft_count_digit(long n, int sign);

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		sign;
	int		digit;

	sign = ft_is_positive(n);
	nb = n;
	if (n < 0)
		nb = -nb;
	digit = ft_count_digit(nb, sign);
	str = (char *)malloc(sizeof(char) * digit + 1);
	if (str == NULL)
		return (NULL);
	if (sign == -1)
		str[0] = '-';
	str[digit] = 0;
	while (nb > 9)
	{
		str[digit-- - 1] = nb % 10 + '0';
		nb = nb / 10;
	}
	str[digit - 1] = nb + '0';
	return (str);
}

static int	ft_is_positive(int n)
{
	if (n >= 0)
		return (1);
	else
		return (-1);
}

static int	ft_count_digit(long n, int sign)
{
	int	cnt;

	cnt = 1;
	if (sign < 0)
		++cnt;
	while (n > 9)
	{
		n = n / 10;
		++cnt;
	}
	return (cnt);
}
