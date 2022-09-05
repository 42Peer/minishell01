/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:43:21 by sumsong           #+#    #+#             */
/*   Updated: 2022/01/12 17:31:33 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;
	size_t			i;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			dst_ptr[i] = src_ptr[i];
			++i;
		}
	}
	else if (src < dst)
	{
		while (len > 0)
		{
			dst_ptr[len - 1] = src_ptr[len - 1];
			--len;
		}
	}
	return (dst_ptr);
}
