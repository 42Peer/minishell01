/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:51:34 by sumsong           #+#    #+#             */
/*   Updated: 2022/01/05 15:28:06 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int value, size_t num)
{
	unsigned char	*ptr;

	ptr = b;
	while (num > 0)
	{
		*ptr++ = (unsigned char)value;
		--num;
	}
	return (b);
}
