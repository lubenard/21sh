#include "libft.h"

void	ft_deltab(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tab[i])
		i++;
	while (j != i)
		free(tab[i]);
	free(tab);
}
