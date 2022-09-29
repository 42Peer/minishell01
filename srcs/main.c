#include "../minishell.h"

void	main_init(int *p_flag, t_struct *p_ds, int argc, char **argv)
{
	*p_flag = 0;
	p_ds->head_token = NULL;
	p_ds->root_node = NULL;
	(void)argc;
	(void)argv;
}

void	about_prompt(char **p_str)
{
	signal_handler();
	*p_str = readline("minishell > ");
	if (!(*p_str))
		exit(set_or_get_status(-1));
	in_process_signal_handler();
	add_history(*p_str);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_struct	ds;
	int			syntx_erred;

	main_init(&syntx_erred, &ds, argc, &argv);
	make_env_array(envp);
	while (1)
	{
		about_prompt(&str);
		ds.head_token = tokenize(str);
		if (ds.head_token == NULL)
		{
			free(str);
			continue ;
		}
		if (make_tree(&ds) == ERROR
			|| (!tree_parser(ds.root_node, &syntx_erred) && syntx_erred))
		{
			cleaner(str, &ds, NULL);
			continue ;
		}
		execute(&ds);
		cleaner(str, &ds, NULL);
	}
	return (0);
}
