#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_struct	ds;
	int			flag;

	flag = 0;
	ds.head_token = NULL;
	ds.root_node = NULL;
	if (argc)
		(void)argv;
	make_env_array(envp);
	while (1)
	{
		signal_handler();
		str = readline("minishell > ");
		if (!str)
			exit(130);
		in_process_signal_handler();
		add_history(str);
		ds.head_token = tokenize(str);
		if (ds.head_token == NULL)
		{
			free(str);
			continue ;
		}
		if (make_tree(&ds) == 0
			|| (!tree_parser(ds.root_node, &flag) && flag == 1))
		{
			cleaner(str, &ds, NULL);
			continue ;
		}
		execute(&ds);
		cleaner(str, &ds, NULL);
	}
	return (0);
}
