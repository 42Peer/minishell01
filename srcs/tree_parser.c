/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:21:50 by kyolee            #+#    #+#             */
/*   Updated: 2022/09/26 18:21:46 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cmd_parser(t_node *node)
{
	char	*new_content;

	if (!node)
		return ;
	cmd_parser(node->left);
	cmd_parser(node->right);
	if (node->type == T_WORD)
	{
		new_content = delquote(node->content, NULL);
		free(node->content);
		node->content = new_content;
	}
}

static void	check_invalid_redir_content(t_node *node, int *flag)
{
	if (ft_strncmp(node->content, ">>", 3) != 0
		&& ft_strncmp(node->content, ">", 2) != 0
		&& ft_strncmp(node->content, "<", 2) != 0
		&& ft_strncmp(node->content, "<<", 3) != 0)
	{
		printf("Error: syntax error in redir_parser!\n");
		set_or_get_status(258);
		*flag = 1;
	}
}

static void	redir_parser(t_node *node, int *flag)
{
	int		quoted;
	char	*new_content;

	quoted = 0;
	if (!node)
		return ;
	if (node->type == T_REDIR)
	{
		check_invalid_redir_content(node, flag);
		if (ft_strncmp(node->content, "<<", 3) == 0)
		{
			new_content = delquote(node->right->content, &quoted);
			free(node->right->content);
			node->type = T_HEREDOC;
			node->right->content = new_content;
			func_heredoc(node, node->right->content, quoted);
		}
	}
	else
	{
		redir_parser(node->right, flag);
		redir_parser(node->left, flag);
	}
}

int	tree_parser(t_node *node, int *flag)
{
	if (!(node))
		return (0);
	if (node->type == N_PHRASE)
	{
		redir_parser(node->left, flag);
		cmd_parser(node->right);
	}
	else
	{
		tree_parser(node->left, flag);
		tree_parser(node->right, flag);
	}
	return (0);
}
