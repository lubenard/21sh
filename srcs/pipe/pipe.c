/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/29 16:48:54 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh21.h"

int		count_args(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	printf("Il y a %d elements\n", i);
	return (i);
}

char	***compact_command(char *command)
{
	char	***ret;
	char	**argv;
	int		i;

	i = 0;
	argv = ft_strsplit(command, '|');
	if (!(ret = (char ***)malloc(sizeof(char **) * (count_args(argv) + 1))))
		return (NULL);
	while (argv[i])
	{
		argv[i] = ft_strtrim(argv[i]);
		ret[i] = ft_strsplit(argv[i], ' ');
		printf("re[%d] vaut %s\n", i, ret[i][0]);
		i++;
		free(argv[i]);
	}
	free(argv);
	printf("ret[%d] vaut NULL\n", i);
	ret[i] = NULL;
	return (ret);
}
int		free_pipe(char ***command)
{
	int		i;
	int		e;
	int		k;

	k = 0;
	i = 0;
	e = 0;
	printf("Je suis lance\n");
	while (command[i])
	{
		printf("Le debut de la chaine vaut %s\n",command[i][0]);
		/*while (command[i][e])
		{
			printf("Je free %s\n", command[i][e]);
			//free(command[i][e]);
			e++;
		}
		//free(command[i]);*/
		i++;
	}
	return (0);
}

int		multiple_pipe(t_env *lkd_env, char ***command, char **path)
{
	int		link[2];
	pid_t	pid;
	int		fd_in;
	int		i;

	i = 0;
	fd_in = 0;
	while (*command != NULL)
	{
		printf("find_path vaut = %s\n", ft_strjoin(find_path(path, (*command)[0]), (*command)[0]));
		if (pipe(link) == -1 || (pid = fork()) == -1)
			return (0);
		if (pid == 0)
		{
			dup2(fd_in, 0);
			if (*(command + 1) != NULL)
				dup2(link[1], 1);
			close(link[0]);
			printf("command vaut %s et command[1] vaut %s et command[2] = %s\n", (*command)[0], (*command)[1], (*command)[2]);
			execve(ft_strjoin(find_path(path, (*command)[0]), (*command)[0]), *command, compact_env(lkd_env));
			perror("error: ");
			break ;
		}
		else
		{
			wait(NULL);
			close(link[1]);
			fd_in = link[0];
			command++;
			i++;
		}
	}
	free_pipe(command);
	return (0);
}

int		handle_pipe(t_env *lkd_env, char **path, char *command)
{
	multiple_pipe(lkd_env, compact_command(command), path);
	return (0);
}
