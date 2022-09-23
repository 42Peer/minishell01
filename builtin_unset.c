#include "minishell.h"

void    builtin_unset(char **args)
{
    (void)args;
    printf("unset\n");
    set_or_get_status(0);
}