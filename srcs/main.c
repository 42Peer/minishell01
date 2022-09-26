#include "../minishell.h"

void	main_init(int *p_flag, t_struct *p_ds, int argc, char ***p_argv)
{
	*p_flag = 0;
	p_ds->head_token = NULL;
	p_ds->root_node = NULL;
	if (argc)
		(void)(*p_argv);
}

void	about_prompt(char **p_str)
{
	signal_handler();
	*p_str = readline("minishell > ");
	if (!(*p_str))
		exit(130);
	in_process_signal_handler();
	add_history(*p_str);
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
		about_prompt(&str);
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
