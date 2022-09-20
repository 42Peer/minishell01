#include "minishell.h"

t_env	*env_lstnew(char *env)
{
	t_env	*new;
	char	**split;

	new = malloc(sizeof(t_env));
	if (!new)
		system_call_error();
	split = ft_split(env, '=');
	new->key = ft_strdup(split[0]);
	new->value = ft_strdup(split[1]);
	free(split[0]);
	free(split[1]);
	free(split);
	new->next = NULL;
	return (new);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*cur;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	make_env_list(char **envp, t_struct *ds)
{
	// t_env	*head;
	t_env	*env;
	int		i;

	i = 0;
	ds->head_env = NULL;
	while (envp && envp[i])
	{
		env = env_lstnew(envp[i]);
		if (!env)
			clean_exit(ERROR, NULL, NULL, ds);
		env_lstadd_back(&(ds->head_env), env);
		++i;
	}
	// ds->head_env = head;
}

void	env_lstclear(t_env **lst)
{
	t_env	*cur;

	while (*lst)
	{
		cur = *lst;
		if (cur->key)
			free(cur->key);
		if (cur->value)
			free(cur->value);
		*lst = (*lst)->next;
		cur->next = NULL;
		free(cur);
	}
}

// tmp func
void	env_lstiter(t_env *lst, void (*f)(char *))
{
	while (lst)
	{
		f(lst->key);
		f(lst->value);
		lst = lst->next;
	}
}
