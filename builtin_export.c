#include "minishell.h"

void    builtin_export(char **args)
{
    (void)args;
    printf("export\n");
    set_or_get_status(0);
}