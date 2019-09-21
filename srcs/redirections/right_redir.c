/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:00:39 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/21 12:31:28 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Have to rewrite the redir: here is how it works
** 1) create files
** 2) make the good redir
** 3) execute the command
*/

/*char	**save_filename(char **tab, int i)
{
	int		nbr_elem;
	char	**filename;
	int		k;
	char	*tmp;
//	char	*tmp2;

	k = 0;
	nbr_elem = count_elem_redir(tab, i);
	if (!(filename = (char **)malloc(sizeof(char *) * (nbr_elem + 1))))
		return (NULL);
	while (!ft_strchr(tab[i], '>'))
	{
		printf("Je passe %s\n", tab[i]);
		i++;
	}
	i++;
	while (tab[i])
	{
		printf("[Save Filename] Je regarde %s\n", tab[i]);
		if (!ft_strchr(tab[i], '>'))
		{
			filename[k] = tab[i];
			printf("filename[%d] = '%s'\n", k, filename[k]);
			k++;
		}
		else
		{
			if (ft_strcmp(tmp = extract_first(tab[i], '>'), ""))
			{
				filename[k] = tmp;
				printf("filename[%d] = '%s'\n", k, filename[k]);
				k++;
			}
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
		if (access(filenames[i], F_OK) == -1)
		{
			printf("Je cree %s\n", filenames[i]);
			if ((file = open(filenames[i], O_CREAT, 0666) <= 0))
				return (1);
			close(file);
		}
		else
			printf("Le fichier %s existe deja\n", filenames[i]);
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
	tab[0] = ft_strndup(output_std, ft_strlen(output_std) - 1);
	tab[1] = ft_strndup(output_err, ft_strlen(output_err) - 1);
	return(tab);
}

int		fill_file(char **filenames, char **output, char **tab)
{
	int		out;
	int		i;

	i = 0;
	(void)filenames;
	while (tab[i])
		printf("tab[i] = %s\n", tab[i++]);
	i = ft_tablen(tab) - 1;
	while (i != 0)
	{
		if (!ft_strchr(tab[i], '>'))
		{
			printf("J'ouvre %s\n", tab[i]);
			printf("tab[%d - 1] = %s\n", i, tab[i - 1]);
			if (ft_strstr(tab[i - 1], ">>"))
			{
				printf("I append to the file\n");
				out = open(tab[i], O_APPEND | O_WRONLY);
			}
			else if (ft_strchr(tab[i - 1], '>'))
			{
				printf("I write to the file\n");
				out = open(tab[i], O_WRONLY | O_TRUNC);
			}
			if (tab[i - 1][0] == '2')
				ft_putendl_fd(output[1], out);
			else
				ft_putendl_fd(output[0], out);
			close(out);
		}
		//free(filenames[i]);
		i--;
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
*/
void	save_redir(char *command, char *content)
{
	char **tab;
	char **filenames;

	(void)command;
	(void)tab;
	(void)filenames;
	(void)content;
	//tab = prepare_tab(command, '>');
	//filenames = save_filename(tab, 1);
	//create_file(filenames, tab);
	////fill_file(filenames, content, tab);
}
/*
** ----------------------New redirections ------------------
*/

int		create_file(char **filenames)
{
	int i;
	int file;

	i = 0;
	while (!ft_strchr(filenames[i], '>'))
	{
		printf("Je passe %s\n", filenames[i]);
		i++;
	}
	i++;
	while (filenames[i])
	{
		if (access(filenames[i], F_OK) == -1 && !ft_strchr(filenames[i], '>'))
		{
			printf("Je cree %s\n", filenames[i]);
			if ((file = open(filenames[i], O_CREAT, 0666) < 0))
				return (display_error("ymarsh: error while creating file ",
					filenames[i]));
			close(file);
		}
		else
			printf("Le fichier %s existe deja\n", filenames[i]);
		i++;
	}
	return (0);
}

int		check_redir(char **command)
{
	int		i;
	int		last_char;

	i = 0;
	while (command[i])
	{
		last_char = ft_strlen(command[i]) - 1;
		if (ft_occur(command[i], '>') >= 3)
			return (print_error_redirect(">"));
		else if (!command[i + 1] && command[i][last_char] == '>')
			return (print_error_redirect("\\n"));
		else if (command[i][last_char] == '>'
			&& command[i + 1][0] == '>')
			return (print_error_redirect(command[i + 1]));
		i++;
	}
	return (0);
}

int		link_files(char **command)
{
	int i;
	int file;

	i = 0;
	while (!ft_strchr(command[i], '>'))
	{
		printf("[link_file] Je passe %s\n", command[i]);
		i++;
	}
	printf("Avant de boucler je suis sur %s\n", command[i]);
	while (command[i])
	{
		printf("[link_file] Je boucle\n");
		if (!ft_strcmp(command[i], ">"))
		{
			printf("Je vais faire une redir sur >\n");
			i++;
			while (command[i] && !ft_strchr(command[i], '>'))
			{
				printf("J'ouvre %s\n", command[i]);
				file = open(command[i], O_WRONLY | O_TRUNC);
				printf("Je dup2(%d, 1)\n", file);
				dup2(file, 1);
				i++;
			}
		}
		if (!ft_strcmp(command[i], "2>"))
		{
			printf("Je vais faire une redir sur 2>\n");
			i++;
			while (command[i] && !ft_strchr(command[i], '>'))
			{
				printf("J'ouvre %s\n", command[i]);
				file = open(command[i], O_WRONLY | O_TRUNC);
				printf("Je dup2(%d, 1)\n", file);
				dup2(file, 2);
				i++;
			}
		}
	}
	return (0);
}

int		exec_command_redir(t_hustru *big_struc, char **command)
{
	char	**compact;
	int		i;
	int		e;
	//pid_t	pid;

	i = 0;
	e = 0;
	printf("je rentre dans exec_command_redir\n");
	while (command[i] && !ft_strchr(command[i], '>'))
		i++;
	if (!(compact = malloc(sizeof(char *) * (i + 1))))
		return (1);
	while (e != i)
	{
		compact[e] = command[e];
		e++;
	}
	compact[e] = NULL;
	int j = 0;
	while (compact[j])
		printf("Compact = %s\n", compact[j++]);
	
	basic_command(big_struc, compact);
	close(3);
	return (0);
}

int		arrow_right(t_hustru *big_struc, char **command)
{
	(void)big_struc;
	//int *open_fd;
/*	int		i = 0;
	char	*extract;
	int		k = 0;
	char	*tab[50];
	char	**filenames;
	char	**output;

	(void)big_struc;
	while (!ft_strchr(command[i], '>'))
	{
		printf("[Redirections]: Je passe sur %s\n", command[i]);
		i++;
	}
	printf("[Redirections]: Je m'arrete sur %s\n", command[i]);
	if (command[i][0] != '>')
	{
		extract = extract_first(command[i], '>');
		printf("[Redirections] extract vaut %s\n", extract);
	}
	while (k != i)
	{
		printf("Je copie %s\n", command[k]);
		tab[k] = command[k];
		k++;
	}
	tab[k] = NULL;
	filenames = save_filename(command, i); //merge save_filename and create_file
	create_file(filenames);
	output = get_output_of_command(big_struc, tab);
	fill_file(filenames, output, command);
	return (0);*/
	if (check_redir(command))
	{
		printf("Je detecte une erreur et retourne 1\n");
		return (1);
	}
	create_file(command);
	link_files(command);
	exec_command_redir(big_struc, command);
	return (0);
}
