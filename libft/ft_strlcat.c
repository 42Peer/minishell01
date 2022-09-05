/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:50:16 by sumsong           #+#    #+#             */
/*   Updated: 2022/01/24 23:33:43 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;

	i = 0;
	j = 0;
	dst_len = ft_strlen(dst);
	if (dstsize < ft_strlen(dst) + 1)
		return (dstsize + ft_strlen(src));
	while (dst[i])
		++i;
	while (src[j] && i + 1 < dstsize)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst_len + ft_strlen(src));
}
