/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:42:44 by sumsong           #+#    #+#             */
/*   Updated: 2022/09/20 20:31:51 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_token	*ft_lstnew(int type, char *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		system_call_error();
	new->type = type;
	new->content = content;
	new->next = NULL;
	return (new);
}
