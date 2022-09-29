#include "../../minishell.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr++ = 0;
		--n;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ary;

	ary = malloc(count * size);
	if (ary == NULL)
		system_call_error(ALLOC_FAIL);
	ft_bzero(ary, count * size);
	return (ary);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	if (!dst && !src)
		return (NULL);
	dst_ptr = dst;
	src_ptr = (unsigned char *)src;
	while (n > 0)
	{
		*dst_ptr++ = *src_ptr++;
		--n;
	}
	return (dst);
}

void	check_args(char **args)
{
	if (!(args[1]))
		return ;
	if (args[2] != 0)
	{
		printf("too many arguments\n");
		set_or_get_status(GENERAL_ERROR);
		return ;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	if (!split)
		return ;
	while (split && split[++i])
		free(split[i]);
	free(split);
}

void	print_content(char *str)
{
	printf("%s", str);
}
