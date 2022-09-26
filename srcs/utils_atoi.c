#include "../minishell.h"
#include <limits.h>

static int	ft_sign_env_array(const char *str);

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (4);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long	nb;
	int		i;
	int		sign;

	nb = 0;
	i = 0;
	sign = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		++i;
	if (str[i] == '+' || str[i] == '-')
		sign = ft_sign_env_array(&str[i++]);
	while (str[i] && ft_isdigit(str[i]))
	{
		if (sign == 1 && ((nb > LONG_MAX / 10)
				|| (nb == LONG_MAX / 10 && str[i] >= '7')))
			return (-1);
		else if (sign == -1 && ((nb > LONG_MIN / 10 * -1)
				|| (nb == LONG_MIN / 10 * -1 && str[i] >= '8')))
			return (0);
		nb = nb * 10 + str[i++] - '0';
	}
	return (sign * (int)nb);
}

static int	ft_sign_env_array(const char *str)
{
	if (*str == '+')
		return (1);
	else
		return (-1);
}
