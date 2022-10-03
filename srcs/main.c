#include "../minishell.h"

void	main_init(
	int *syntx_erred, t_head *p_head, int argc, char **argv)
{
	*syntx_erred = 0;
	p_head->token = NULL;
	p_head->node = NULL;
	(void)argc;
	(void)argv;
}

void	about_prompt(char **p_str)
{
	set_or_get_heredoc_status(0);
	signal_handler();
	*p_str = readline("smash > ");
	if (!(*p_str))
		exit(set_or_get_status(-1));
	add_history(*p_str);
}

void	tree_parser_error(char *str, t_head *p_head, int *syntax_erred)
{
	if (*syntax_erred)
		printf("Error: syntax error!\n");
	cleaner(str, p_head, NULL);
	*syntax_erred = 0;
}

int	loop_shell_prompt(t_head *p_head, int *p_syntx_erred)
{
	char	*user_input_str;

	while (1)
	{
		about_prompt(&user_input_str);
		p_head->token = tokenize(user_input_str);
		if (p_head->token == NULL)
		{
			free(user_input_str);
			continue ;
		}
		if (make_tree(p_head) == ERROR
			|| (!tree_parser(p_head->node, p_syntx_erred) && *p_syntx_erred))
		{
			tree_parser_error(user_input_str, p_head, p_syntx_erred);
			continue ;
		}
		if (set_or_get_heredoc_status(GET) == CTRL_C)
		{
			cleaner(user_input_str, p_head, NULL);
			continue ;
		}
		execute(p_head);
		cleaner(user_input_str, p_head, NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_head		head;
	int			syntx_erred;

	main_init(&syntx_erred, &head, argc, argv);
	make_g_env_array(envp);
	loop_shell_prompt(&head, &syntx_erred);
	return (0);
}
