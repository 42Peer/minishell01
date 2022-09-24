/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:58:37 by sumsong           #+#    #+#             */
/*   Updated: 2022/09/25 00:09:20 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ary;

	ary = malloc(count * size);
	if (ary == NULL)
		system_call_error(ALLOC_FAIL);
	ft_bzero(ary, count * size);
	return (ary);
}
