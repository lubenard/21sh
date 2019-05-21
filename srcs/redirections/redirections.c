/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/21 18:02:22 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh21.h"

char	**prepare_tab(char *command, char signe)
{
	int		i;
	char	**tab;
	char	*tmp;

	i = 0;
	tab = ft_strsplit(command, signe);
	while (tab[i])
	{
		tmp = ft_strdup(tab[i]);
		free(tab[i]);
		tab[i] = ft_strtrim(tmp);
		free(tmp);
		i++;
	}
	i = 0;
	while (tab[i])
		printf("tab[i] vaut '%s'\n", tab[i++]);
	return (tab);
}

void	ft_str_start_cat(char *dest, const char *src, int start)
{
	int k;

	k = 0;
	while (dest[k])
		k++;
	while (src[start])
		dest[k++] = src[start++];
	if (ft_isalnum(dest[k - 1]))
	{
		dest[k] = ' ';
		dest[k + 1] = '\0';
	}
	else
		dest[k] = '\0';
}

int		pass_filename(char **tab, int i)
{
	int e;

	e = 0;
	while (ft_isalnum(tab[i][e]))
		e++;
	while (tab[i][e] == ' ' || tab[i][e] == '\t')
		e++;
	return (e);
}

int		count_elem_redir(char **tab, int i)
{
	int elem;

	elem = 0;
	while (tab[i])
	{
		if (tab[i][0] != 0)
			elem++;
		i++;
	}
	return (elem);
}

char	**save_filename(char **tab, int i)
{
	int		e;
	int		nbr_elem;
	char	**filename;
	int		k;

	e = 0;
	k = 0;
	printf("i vaut %d\n", i);
	nbr_elem = count_elem_redir(tab, i);
	printf("nbr_elem = %d\n", nbr_elem);
	if (!(filename = (char **)malloc(sizeof(char *) * (nbr_elem + 1))))
		return (NULL);
	while (i - 1 < nbr_elem)
	{
		while (tab[i][e] && tab[i][e] != ' ')
			e++;
		filename[k] = ft_strsub(tab[i], 0, e);
		printf("filename[%d] = %s\n", k, filename[k]);
		k++;
		e = 0;
		i++;
	}
	filename[k] = NULL;
	return (filename);
}

int		print_error_redirect(char **tab)
{
	int i;

	i = 0;
	ft_putendl_fd("ymarsh: parse error near '\\n'", 2);
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (1);
}

int		check_errors_redirect(char **tab, char *command, int i)
{
	if (command[ft_strlen(command) - 1] == '>')
		return (print_error_redirect(tab));
	while (tab[i])
	{
		if (tab[i][0] == '\0')
			return (print_error_redirect(tab));
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
		file = open(filenames[i], O_CREAT | O_TRUNC, 0666);
		if (file <= 0)
			return (1);
		i++;
	}
	return (0);
}

void	double_arrow_left(t_env *lkd_env, char *command)
{
	(void)command;
	(void)lkd_env;

}

void	double_arrow_right(t_env *lkd_env, char *command)
{
	/*
	** Append to file or create it
	*/
	(void)command;
	(void)lkd_env;

}

void	simple_arrow_left(t_env *lkd_env, char *command)
{
	(void)command;
	(void)lkd_env;
	/*
	** Send into input programm
	*/
}

char	*get_output_of_command(char *path, char **argv, char **env)
{
	int		link[2];
	pid_t	pid;
	char	output[50000];
	int		wait_pid;

	if (pipe(link) == -1)
		return (NULL);
	if ((pid = fork()) == -1)
		return (NULL);
	signal(SIGINT, handle_signals_proc);
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
		while ((wait_pid = wait(&pid)) > 0);
		close(link[1]);
		read(link[0], output, 50000);
	}
	free_after_exec(path, argv, env);
	return (ft_strndup(output, ft_strlen(output) -1));
}

int		fill_file(char **filenames, char *command, char av[131072], t_env *lkd_env)
{
	int		out;
	int		i;
	char	*ret_command;
	char	**argv;

	i = 0;
	(void)command;
	argv = ft_strsplit(av, ' ');
	ret_command = get_output_of_command(argv[0],
	argv, compact_env(lkd_env));
	while (filenames[i])
	{
		out = open(filenames[i], O_WRONLY);
		ft_putendl_fd(ret_command, out);
		close(out);
		i++;
	}
	return (0);
}

void	simple_arrow_right(t_env *lkd_env, char *command)
{
	char	**tab;
	int		i;
	char	av[131072];
	char	**filenames;
	int		e;
	/*
	** Create the file or crush it
	** NOTES : arrow is creating the files before executing command
	*/
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
		ft_str_start_cat(av, tab[i], e);
		printf("av = '%s'\n", av);
		i++;
	}
	create_file(filenames);
	fill_file(filenames, command, av, lkd_env);
}

void	redirections(t_env *lkd_env, char *path, char *command)
{
	(void)path;
	if (ft_strstr(command, "<<"))
		double_arrow_left(lkd_env, command);
	else if (ft_strstr(command, ">>"))
		double_arrow_right(lkd_env, command);
	else if (ft_strchr(command, '<'))
		simple_arrow_left(lkd_env, command);
	else if (ft_strchr(command, '>'))
		simple_arrow_right(lkd_env, command);
}
