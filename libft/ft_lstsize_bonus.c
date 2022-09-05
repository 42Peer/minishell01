/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:34:53 by sumsong           #+#    #+#             */
/*   Updated: 2022/09/05 18:15:35 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_token *lst)
{
	int		cnt;

	cnt = 0;
	while (lst)
	{
		++cnt;
		lst = lst->next;
	}
	return (cnt);
}
