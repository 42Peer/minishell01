/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:10:10 by sumsong           #+#    #+#             */
/*   Updated: 2022/01/24 23:44:16 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int chr)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)chr)
			return ((char *)&str[i]);
		++i;
	}
	if ((char)chr == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
