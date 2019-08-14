/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:00:39 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/14 11:25:58 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	**save_filename(char **tab, int i)
{
	int		e;
	int		nbr_elem;
	char	**filename;
	int		k;
	int		m;

	k = 0;
	nbr_elem = count_elem_redir(tab, i);
	if (!(filename = (char **)malloc(sizeof(char *) * (nbr_elem + 1))))
		return (NULL);
	while (i - 1 < nbr_elem)
	{
		m = 0;
		while ((tab[i][m] == '>' || tab[i][m] == ' '
			|| tab[i][m] == '\t') && tab[i][m])
			m++;
		e = m;
		while (tab[i][e] && tab[i][e] != ' ')
			e++;
		filename[k] = ft_strsub(tab[i], m, e);
		printf("filename[%d] = '%s'\n", k, filename[k]);
		k++;
		i++;
	}
	filename[k] = NULL;
	return (filename);
}

int		check_errors_redirect(char **tab, char *command, int i)
{
	if (command[ft_strlen(command) - 1] == '>')
		return (print_error_redirect(tab, "'\\n'"));
	while (tab[i])
	{
		if (tab[i][0] == '\0' || (tab[i][ft_strlen(tab[i]) - 1] == '>'))
			return (print_error_redirect(tab, "'>'"));
		i++;
	}
	return (0);
}

int		create_file(char **filenames, char **tab)
{
	int i;
	int file;
	int e;

	i = 0;
	e = 1;
	while (filenames[i])
	{
		if (tab[e][0] == '>')
			file = open(filenames[i], O_CREAT, 0666);
		else
			file = open(filenames[i], O_CREAT | O_TRUNC, 0666);
		if (file <= 0)
			return (1);
		close(file);
		i++;
		e++;
	}
	return (0);
}

char	*get_output_of_command(char *path, char **argv, char **env)
{
	int		link[2];
	pid_t	pid;
	char	output[50000];
	int		wait_pid;

	if (pipe(link) == -1 || (pid = fork()) == -1)
		return (NULL);
	if (pid == 0)
	{
		dup2(link[1], 1);
		close(link[0]);
		close(link[1]);
		execve(path, argv, env);
		wait(&pid);
	}
	else
	{
		while ((wait_pid = wait(&pid)) > 0)
			;
		close(link[1]);
		read(link[0], output, 50000);
	}
	free_after_exec(path, argv, env);
	return (ft_strndup(output, ft_strlen(output) - 1));
}

int		fill_file(char **filenames, char *ret_command, char **tab)
{
	int		out;
	int		i;

	i = 0;
	while (filenames[i])
	{
		if (tab[i + 1][0] == '>')
			out = open(filenames[i], O_APPEND | O_WRONLY);
		else
			out = open(filenames[i], O_WRONLY);
		ft_putendl_fd(ret_command, out);
		close(out);
		free(filenames[i]);
		i++;
	}
	free(ret_command);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	free(filenames);
	return (0);
}

char	*exec_command_redir(t_env *lkd_env, char **path, char av[131072])
{
	char	**argv;
	char	*ret_command;
	char	*normal_path;

	argv = ft_strsplit(av, ' ');
	normal_path = find_path(path, argv[0]);
	ret_command = get_output_of_command(normal_path,
		argv, compact_env(lkd_env));
	return (ret_command);
}

void	save_redir(char *command, char *content)
{
	char **tab;
	char **filenames;

	tab = prepare_tab(command, '>');
	filenames = save_filename(tab, 1);
	create_file(filenames, tab);
	fill_file(filenames, content, tab);
}

void	arrow_right(t_env *lkd_env, char **path, char *command)
{
	char	**tab;
	int		i;
	char	av[131072];
	char	**filenames;
	int		e;

	i = 1;
	ft_bzero(av, 131072);
	tab = prepare_tab(command, '>');
	ft_str_start_cat(av, tab[0], 0);
	if (check_errors_redirect(tab, command, i) == 1)
		return ;
	filenames = save_filename(tab, i);
	while (tab[i])
	{
		e = pass_filename(tab, i);
		if (tab[i][0] == '>')
			e++;
		ft_str_start_cat(av, tab[i], e);
		i++;
	}
	create_file(filenames, tab);
	fill_file(filenames, exec_command_redir(lkd_env, path, av), tab);
}
