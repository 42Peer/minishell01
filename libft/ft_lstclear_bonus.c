/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:52:51 by sumsong           #+#    #+#             */
/*   Updated: 2022/09/05 18:27:16 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_token **lst)
{
	t_token	*cur;

	while (*lst)
	{
		cur = *lst;
		cur->type = 0;//NONE
		if (cur->content)
			free(cur->content);
		*lst = (*lst)->next;
		cur->next = NULL;
		free(cur);
	}
}
