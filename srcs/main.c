#include "../minishell.h"

void	main_init(int *p_flag, t_struct *p_ds, int argc, char ***p_argv)
{
	*p_flag = 0;
	p_ds->head_token = NULL;
	p_ds->root_node = NULL;
	if (argc)
		(void)(*p_argv);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_struct	ds;
	int			flag;

	main_init(&flag, &ds, argc, &argv);
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
		// printf("token \n =--------------------------------");
		ft_lstiter(ds.head_token, print_content);
		if (make_tree(&ds) == 0
			|| (!tree_parser(ds.root_node, &flag) && flag == 1))
		{
			cleaner(str, &ds, NULL);
			continue ;
		}
		// printf("tree \n =--------------------------------");
		ft_traverse(ds.root_node);
		execute(&ds);
		cleaner(str, &ds, NULL);
	}
	return (0);
}
