/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:22:12 by kyolee            #+#    #+#             */
/*   Updated: 2022/09/26 19:24:37 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*e_make_expnd_str(char *str)
{
	int		i;
	char	*expnd_str;

	i = -1;
	expnd_str = NULL;
	while (str[++i])
	{
		if (str[i] == '$')
			expnd_str = ft_strjoin(expnd_str, dollar_sign(str, &i));
		else
			expnd_str = save(expnd_str, str[i], ft_strlen(expnd_str));
	}
	if (!expnd_str)
		system_call_error(ALLOC_FAIL);
	return (expnd_str);
}

static void	e_here_write(int fd, char *str, size_t len)
{
	if (write(fd, str, len) == -1)
	{
		close(fd);
		system_call_error(errno);
	}
}

static void	e_write_heredoc_str_to_file(
				int fd,
				char *delimiter,
				int quoted_delimit)
{
	char	*expnd_str;
	char	*str;

	while (1)
	{
		expnd_str = ft_strdup("");
		str = readline("> ");
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter) + 1))
			break ;
		if (!quoted_delimit)
		{
			expnd_str = e_make_expnd_str(str);
			e_here_write(fd, expnd_str, ft_strlen(expnd_str));
		}
		else
			e_here_write(fd, str, ft_strlen(str));
		e_here_write(fd, "\n", 1);
		free(str);
		free(expnd_str);
	}
	free(str);
	free(expnd_str);
}

static void	change_heredoc_node_to_redirect(t_node *node, char *filename)
{
	if (node->content)
		free(node->content);
	node->content = ft_strdup("<");
	if (node->right->content)
		free(node->right->content);
	node->right->content = filename;
}

char	**func_heredoc(t_node *node, char *delimiter, int quoted)
{
	int		fd;
	char	*filename;

	fd = -1;
	filename = ft_strdup("/tmp/here_doc_0");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0666);
	while (fd == -1)
	{
		filename = save(filename, '0', ft_strlen(filename));
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0666);
	}
	e_write_heredoc_str_to_file(fd, delimiter, quoted);
	close(fd);
	change_heredoc_node_to_redirect(node, filename);
	return (NULL);
}
