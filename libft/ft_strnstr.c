/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:20:16 by sumsong           #+#    #+#             */
/*   Updated: 2022/01/24 23:59:52 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	if (needle_len > ft_strlen(haystack) || len == 0)
		return (NULL);
	i = 0;
	while (i <= len - needle_len)
	{
		if (*(haystack + i) == needle[0])
		{
			if (ft_strncmp(haystack + i, needle, needle_len) == 0)
				return ((char *)haystack + i);
		}
		++i;
	}
	return (NULL);
}
