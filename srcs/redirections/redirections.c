/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/03 16:49:24 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** NOTES : arrow is creating the files before executing command
*/

int		print_error_redirect(char **tab, char *code)
{
	int i;

	i = 0;
	ft_putstr_fd("ymarsh: parse error near ", 2);
	ft_putendl_fd(code, 2);
	ft_deltab(tab);
	return (1);
}

char	**prepare_tab(char *command, char signe)
{
	int		i;
	char	**tab;
	char	*tmp;

	i = 0;
	tab = ft_strsplit_redir(command, signe);
	while (tab[i])
	{
		printf("tab[%d] vaut %s\n", i,tab[i]);
		tmp = ft_strdup(tab[i]);
		free(tab[i]);
		tab[i] = ft_strtrim(tmp);
		free(tmp);
		i++;
	}
	return (tab);
}

void	redir_and_pipe(t_hustru *big_struc, char **command)
{
	char **arg;
	int i = 0;
	int		link[2];
	pid_t	pid;
	char	output[50000];
	int		wait_pid;

	(void)command;
	(void)big_struc;
	arg = ft_strsplit_redir(command[0], '>');
	while (arg[i])
		printf("Element vaut %s\n", arg[i++]);
	if (pipe(link) == -1 || (pid = fork()) == -1)
		return ;
	if (pid == 0)
	{
		dup2(link[1], 1);
		close(link[0]);
		close(link[1]);
		handle_pipe(big_struc, arg[0]);
		exit(0);
	}
	else
	{
		while ((wait_pid = wait(&pid)) > 0)
			;
		close(link[1]);
		read(link[0], output, 50000);
		printf("Output vaut |%s|\n", output);
	}
	save_redir(big_struc->line, ft_strndup(output, ft_strlen(output) - 1));
}

void	double_redir(t_hustru *big_struc, char *command)
{
	int		link[2];
	pid_t	pid;
	char	output[50000];
	int		wait_pid;

	if (pipe(link) == -1 || (pid = fork()) == -1)
		return ;
	if (pid == 0)
	{
		dup2(link[1], 1);
		close(link[0]);
		close(link[1]);
		arrow_left(big_struc, extract_first(command, '>'));
		exit(0);
	}
	else
	{
		while ((wait_pid = wait(&pid)) > 0)
			;
		close(link[1]);
		read(link[0], output, 50000);
	}
	save_redir(big_struc->line, ft_strndup(output, ft_strlen(output) - 1));
}

int		arrow_right2(t_hustru *big_struc, char **command)
{
	int		i = 0;
	char	*extract;

	while (!ft_strchr(command[i], '>'))
	{
		printf("[Redirections]: Je passe sur %s\n", command[i]);
		i++;
	}
	printf("[Redirections] Je m'arrete sur %s\n", command[i]);
	if (command[i][0] != '>')
	{
		extract = extract_first(command[i], '>');
		printf("[Redirections] extract vaut %s\n", extract);
	}
	char *argv[] = {"cat", "auteur", NULL};
	char *argv2[] = {"cat", "trucmuche", NULL};
	free(get_output_of_command(big_struc, argv));
	free(get_output_of_command(big_struc, argv2));
	return (0);
}

void	redirections(t_hustru *big_struc, char *command, char **parsed_command)
{
	if (ft_strchr(command, '<') && ft_strchr(command, '>'))
		double_redir(big_struc, command);
	else if (ft_strchr(command, '<'))
		arrow_left(big_struc, command);
	//else if (ft_strchr(command, '<<'))
	//	double_arrow_left(big_struc, command);
	else if (ft_strchr(command, '>') || ft_strstr(command, ">>"))
		arrow_right2(big_struc, parsed_command);
}
