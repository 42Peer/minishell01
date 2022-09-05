/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:34:32 by sumsong           #+#    #+#             */
/*   Updated: 2022/01/24 23:50:49 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		search_word;

	ptr = s;
	search_word = c;
	while (n > 0)
	{
		if (*ptr == search_word)
			return ((void *)ptr);
		--n;
		++ptr;
	}
	return (NULL);
}
