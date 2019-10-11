
#include <sh21.h>

int		count_args_triple_tab(char ***tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		handle_pipe(t_hustru *big_struc, char *command)
{

	int		status;
	int		i;
	char	***tab;
	int		*pipes;
	int		e;
	int		j;
	int		k;

	(void)big_struc;
	tab = compact_command(command);
	e = 0;
	j = 0;
	k = 0;
	i = count_args_triple_tab(tab) - 1; // To fix if a pipe is at the end
	printf("I vaut %d\n", i);
	//printf("close fera %d\n", i * 2);
	//printf("wait fera %d\n", i + 1);
	if (!(pipes = (int *)malloc(sizeof(int) * (i * 2))))
		return (0);
	while (e != i * 2)
	{
		//printf("je pipe a + %d\n", e);
		pipe(pipes + e);
		e += 2;
	}
	e = 0;
	while (tab[j])
	{
		if (fork() == 0)
		{
			//dprintf(2, "J'exec tab[%d][0] = %s\n", j, tab[j][0]);
			if (j != 0)
			{
			//	dprintf(2, "dup2(pipes[%d], 0)\n", k);
				dup2(pipes[k], 0);
			}
			if (tab[j + 1] && j != 0)
			{
			//	dprintf(2, "dup2(pipes[%d], 1)\n", k + 3);
				dup2(pipes[k + 3], 1);
			}
			if (j == 0)
			{
			//	dprintf(2, "dup2(pipes[%d], 1)\n", k + 1);
				dup2(pipes[1], 1);
			}
			close_pipe(pipes, i * 2);
			execve(find_path(big_struc->path, tab[j][0]), tab[j], compact_env(big_struc->lkd_env));
		}
		if (j != 0)
			k += 2;
		j++;
	}
	close_pipe(pipes, i * 2);
	while (e < i + 1)
	{
		wait(&status);
		e++;
	}
	free(pipes);
	return(free_pipe(tab));
}
