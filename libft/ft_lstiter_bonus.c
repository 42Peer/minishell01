/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:39 by sumsong           #+#    #+#             */
/*   Updated: 2022/09/05 18:36:14 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_content(char *str)
{
	printf("%s\n", str);
}

void	ft_lstiter(t_token *lst, void (*f)(char *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}