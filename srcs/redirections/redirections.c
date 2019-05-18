/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/18 18:46:58 by lubenard         ###   ########.fr       */
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
	dest[k] = ' ';
	dest[k + 1] = '\0';
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

int count_elem_redir(char **tab, int i)
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
	nbr_elem = count_elem_redir(tab, i);
	printf("nbr_elem = %d\n", nbr_elem);
	if (!(filename = (char **)malloc(sizeof(char *) * nbr_elem)))
		return (NULL);
	while (tab[i])
	{
		while (tab[i][e] && tab[i][e] != ' ')
			e++;
		filename[k] = ft_strsub(tab[i], 0, e);
		printf("filename[%d] = %s\n", k, filename[k]);
		k++;
		e = 0;
		i++;
	}
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
		return(print_error_redirect(tab));
	while (tab[i])
	{
		if (tab[i][0] == '\0')
			return(print_error_redirect(tab));
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
		file = open(filenames[i], O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
		if (file <= 0)
			return (1);
		i++;
	}
	return (0);
}

void	double_arrow_left(char *command)
{
	(void)command;
}

void	double_arrow_right(char *command)
{
	/*
	** Append to file or create it
	*/
	(void)command;
}

void	simple_arrow_left(char *command)
{
	(void)command;
	/*
	** Send into input programm
	*/
}

void	simple_arrow_right(char *command)
{
	char	**tab;
	int		i;
	char	av[131072];
	char	**filenames;
	int		e;

	i = 1;
	ft_bzero(av, 131072);
	tab = prepare_tab(command, '>');
	if (check_errors_redirect(tab, command, i) == 1)
		return ;
	filenames = save_filename(tab, i);
	while (tab[i])
	{
		e = pass_filename(tab, i);
		printf("je suis sur '%c'\n", tab[i][e]);
		ft_str_start_cat(av, tab[i], e);
		printf("buff = '%s'\n", av);
		i++;
	}
	create_file(filenames);
	/*
	** Exec my command with ft_strsplit(av)
	*/
	/*
	** create the file or crush it
	** NOTES : arrow is creating the files before executing command
	*/
}

void	redirections(char *command)
{
	if (ft_strstr(command, "<<"))
		double_arrow_left(command);
	else if (ft_strstr(command, ">>"))
		double_arrow_right(command);
	else if (ft_strchr(command, '<'))
		simple_arrow_left(command);
	else if (ft_strchr(command, '>'))
		simple_arrow_right(command);
}
