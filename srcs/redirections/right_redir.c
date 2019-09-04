/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:00:39 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/04 16:46:28 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	**save_filename(char **tab, int i)
{
	int		nbr_elem;
	char	**filename;
	int		k;

	k = 0;
	nbr_elem = count_elem_redir(tab, i);
	if (!(filename = (char **)malloc(sizeof(char *) * (nbr_elem + 1))))
		return (NULL);
	while(!ft_strchr(tab[i], '>'))
		i++;
	while (tab[i])
	{
		if (!ft_strchr(tab[i], '>'))
		{
			filename[k] = tab[i];
			printf("filename[%d] = '%s'\n", k, filename[k]);
			k++;
		}
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

int		create_file(char **filenames)
{
	int i;
	int file;

	i = 0;
	while (filenames[i])
	{
		//check if file exist first
		file = open(filenames[i], O_CREAT, 0666);
		if (file <= 0)
			return (1);
		close(file);
		i++;
	}
	return (0);
}

char	**get_output_of_command(t_hustru *big_struc, char **argv)
{
	int		link[4];
	pid_t	pid;
	char	output_std[50000];
	char	output_err[50000];
	char	**tab;

	if (!(tab = (char **)malloc(sizeof(char *) * 2))
		|| pipe(link) < 0 || pipe(link + 2) < 0 || (pid = fork()) < 0)
		return (NULL);
	if (pid == 0)
	{
		dup2(link[1], 1);
		dup2(link[3], 2);
		close_pipe(link, 4);
		basic_command(big_struc, argv);
		exit(0);
	}
	else
	{
		wait(&pid);
		close(link[1]);
		close(link[3]);
		read(link[0], output_std, 50000);
		read(link[2], output_err, 50000);
	}
	printf("------------------start-------------------------\n");
	printf("[Exec redir] output_std vaut %s\n", output_std);
	printf("[Exec redir] output_err vaut %s\n", output_err);
	printf("-------------------end-----------------------\n");
	tab[0] = output_std;
	tab[1] = output_err;
	return(tab);
}

int		fill_file(char **filenames, char **output, char **tab)
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
		ft_putendl_fd(output[0], out);
		close(out);
		//free(filenames[i]);
		i++;
	}
	//free(ret_command);
	//ft_deltab(tab);
	//free(filenames);
	return (0);
}

char	*exec_command_redir(t_hustru *big_struc, char **path, char av[131072])
{
	char	**argv;
	//char	*ret_command;
	char	*normal_path;
	(void)big_struc;
	argv = ft_strsplit(av, ' ');
	normal_path = find_path(path, argv[0]);
	//ret_command = get_output_of_command(big_struc, argv);
	return (0);
}

void	save_redir(char *command, char *content)
{
	char **tab;
	char **filenames;

	(void)content;
	tab = prepare_tab(command, '>');
	filenames = save_filename(tab, 1);
	//create_file(filenames, tab);
	//fill_file(filenames, content, tab);
}

void	arrow_right(t_hustru *big_struc, char **path, char *command)
{
	char	**tab;
	int		i;
	char	av[131072];
	char	**filenames;
	int		e;

	(void)path;
	(void)big_struc;
	i = 1;
	ft_bzero(av, 131072);
	tab = prepare_tab(command, '>');
	printf("Tab[0] vaut %s\n", tab[0]);
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
	//create_file(filenames, tab);
	//fill_file(filenames, exec_command_redir(big_struc, path, av), tab);
}
