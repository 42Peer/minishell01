#include "../minishell.h"

char	**func_heredoc(t_node *node, char *delimiter, int quoted)
{
	int		fd;
	int		i;
	char 	*filename;
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
					expnd_str = ft_strjoin(expanded_str, dollar_sign(str, &i));
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
	// (3) 노드 갱신
	// (3-1) << 노드의 content 의 <로 바꿔주기
	if (node->content)
		free(node->content);
	node->content = ft_strdup("<");
	// (3-2) << 노드의 DELIMITER를 heredoc 임시파일로 바꿔주기
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
	// printf("now node type : %s node str : %s\n", token_str[node->type], node->str);
	if (node->type == N_PHRASE)
	{
		redir_parser(node->left, flag);
		cmd_parser(node->right);
	}
	else
	{
		tree_parser(node->left, flag);	// phrase
		tree_parser(node->right, flag);	// 새 프로세스
	}
	return (0);
}
