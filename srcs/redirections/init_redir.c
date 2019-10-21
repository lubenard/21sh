/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 22:04:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 13:28:02 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_command_redir(int **fds, char **command, int j, int *k)
{
	int fd;

	printf("Je supprime les quotes\n");
	remove_quote(&command);
	int jj = 0;
	while (command[jj])
		printf("command[jj] = %s\n", command[jj++]);
	if (access(command[j], F_OK) == -1 && ft_strcmp(command[j - 1], "<<"))
	{
		if ((fd = open(command[j], O_CREAT, 0644) < 0))
			return (display_error("ymarsh: error while creating file ",
			command[j]));
	}
	if ((ft_strstr(command[j - 1], "&>")
	|| ft_strchr(command[j - 1], '>')
	|| ft_strchr(command[j - 1], '<'))
	&& !ft_strstr(command[j - 1], ">&")
	&& !ft_strstr(command[j - 1], "<&")
	&& ft_strcmp(command[j - 1], "<<"))
	{
		//printf("[Fill fds tab] Je rajoute %s\n", command[j]);
		if (ft_occur(command[j - 1], '>') == 1)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_TRUNC);
		else if (ft_occur(command[j - 1], '>') == 2)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_APPEND);
		else if (ft_strchr(command[j - 1], '<'))
			(*fds)[(*k)++] = open(command[j], O_RDONLY);
		//printf("J'ai ouvert %s et sont fd associe est %d\n", command[j], (*fds)[(*k) - 1]);
	}
	else if (ft_strchr(command[j - 1], '>') && ft_strchr(command[j - 1], '<'))
	{
		if (ft_occur(command[j - 1], '>') == 1)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_TRUNC);
		else if (ft_occur(command[j - 1], '>') == 2)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_APPEND);
		else if (ft_strchr(command[j - 1], '<'))
			(*fds)[(*k)++] = open(command[j], O_RDONLY);
	}
	return (0);
}

int		is_command(char ***exec_command, char **command, int j, int *i)
{
	if (j > 0)
	{
		if ((ft_strstr(command[j - 1], "<&")
		|| ft_strstr(command[j - 1], ">&")) && is_digit(command[j - 1]))
		{
			//printf("[Adding to command] Je rajoute %s\n", command[j]);
			(*exec_command)[(*i)++] = command[j];
			return (1);
		}
		else if (!ft_strchr(command[j - 1], '>')
		&& !ft_strchr(command[j - 1], '<'))
		{
			//printf("[Count args redir] Je rajoute %s\n", command[j]);
			(*exec_command)[(*i)++] = command[j];
			return (1);
		}
	}
	else
	{
		//printf("[Adding to command] Je rajoute %s\n", command[j]);
		(*exec_command)[(*i)++] = command[j];
		return (1);
	}
	return (0);
}

int		fill_arrays(char **command, int **fds, char ***exec_command)
{
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 0;
	while (command[j])
	{
		//printf("[filling] Je regarde %s\n", command[j]);
		if ((!ft_strchr(command[j], '>') && !ft_strchr(command[j], '<'))
		|| is_between_quotes(command[j], 3))
		{
			if (!is_command(exec_command, command, j, &i))
			{
				//printf("Je rentre dans commad_redir\n");
				is_command_redir(fds, command, j, &k);
			}
		}
		j++;
	}
	(*exec_command)[i] = NULL;
	return (0);
}


int		init_arrays(char **command, int **fds,
	char ***exec_command, int *fds_size)
{
	int i;
	int fd;

	i = 0;
	fd = 0;
	while (command[i] && !ft_strchr(command[i], '>')
		&& !ft_strchr(command[i], '<'))
		i++;
	if (!(*exec_command = (char **)malloc(sizeof(char *) *
		(count_args_redir(command, i) + 1))))
		return (display_error("ymarsh: error during malloc", NULL));
	if (!(*fds = (int *)malloc(sizeof(int) *
		(*fds_size = count_elem_redir(command, i)))))
		return (display_error("ymarsh: error during malloc", NULL));
	return (fill_arrays(command, fds, exec_command));
}

