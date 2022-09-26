/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:21:50 by kyolee            #+#    #+#             */
/*   Updated: 2022/09/26 15:27:21 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**func_heredoc(t_node *node, char *delimiter, int quoted)
{
	int		fd;
	int		i;
	char	*filename;
	char	*str;
	char	*expnd_str;

	fd = -1;
	filename = ft_strdup("/tmp/here_doc_0");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0666);
	while (fd == -1)
	{
		filename = save(filename, '0', ft_strlen(filename));
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0666);
	}
	while (1)
	{
		expnd_str = ft_strdup("");
		str = readline("> ");
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter) + 1))
			break ;
		if (!quoted)
		{
			i = -1;
			while (str[++i])
			{
				if (str[i] == '$')
					expnd_str = ft_strjoin(expnd_str, dollar_sign(str, &i));
				else
					expnd_str = save(expnd_str, str[i], ft_strlen(expnd_str));
			}
			if (write(fd, expnd_str, ft_strlen(expnd_str)) == -1)
				system_call_error(errno);
		}
		else
			if (write(fd, str, ft_strlen(str)) == -1)
				system_call_error(errno);
		if (write(fd, "\n", 1) == -1)
			system_call_error(errno);
		free(str);
		free(expnd_str);
	}
	free(str);
	free(expnd_str);
	close(fd);
	if (node->content)
		free(node->content);
	node->content = ft_strdup("<");
	if (node->right->content)
		free(node->right->content);
	node->right->content = filename;
	return (NULL);
}

void	cmd_parser(t_node *node)
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

void	redir_parser(t_node *node, int *flag)
{
	int		quoted;
	char	*new_content;

	quoted = 0;
	if (!node)
		return ;
	if (node->type == T_REDIR)
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
