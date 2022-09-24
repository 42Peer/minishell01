#include "minishell.h"

/*
 *			리스트로 만들기


/*
t_env	*env_lstnew(char *env)
{
	t_env	*new;
	char	**split;

	new = malloc(sizeof(t_env));
	if (!new)
		system_call_error(ALLOC_FAIL);
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
*/

*/

/*
 *		배열로 만들기
 */

void	make_env_array(char **envp, t_struct *ds)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		++i;
	env = ft_calloc(i + 1, sizeof(char *));
	if (!env)
		system_call_error(ALLOC_FAIL);
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	ds->env_array = env;
}