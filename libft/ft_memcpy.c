/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:30:11 by sumsong           #+#    #+#             */
/*   Updated: 2022/01/24 23:28:20 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	if (!dst && !src)
		return (NULL);
	dst_ptr = dst;
	src_ptr = (unsigned char *)src;
	while (n > 0)
	{
		*dst_ptr++ = *src_ptr++;
		--n;
	}
	return (dst);
}
