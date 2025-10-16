#include <libft.h>
#include <parse.h>

int	parse_input(char **argv, int *args)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (!argv[i])
			return (i != 4);
		if (safe_atoi(argv[i], args + i))
			return (1);
		if (args[i] < 0)
			return (1);
		i++;
	}
	return (!!argv[i]);
}
