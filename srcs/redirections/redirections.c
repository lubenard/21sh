/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/07/30 18:43:21 by lubenard         ###   ########.fr       */
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
	while (tab[i])
		free(tab[i++]);
	free(tab);
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
		tmp = ft_strdup(tab[i]);
		free(tab[i]);
		tab[i] = ft_strtrim(tmp);
		free(tmp);
		i++;
	}
	return (tab);
}

void	redir_and_pipe(t_env *lkd_env, char **path, char *command)
{
	char **arg;
	int i = 0;
	int		link[2];
	pid_t	pid;
	char	output[50000];
	int		wait_pid;

	arg = ft_strsplit_redir(command, '>');
	while (arg[i])
		printf("Element vaut %s\n", arg[i++]);

	if (pipe(link) == -1 || (pid = fork()) == -1)
		return ;
	if (pid == 0)
	{
		dup2(link[1], 1);
		close(link[0]);
		close(link[1]);
		handle_pipe(lkd_env, path, arg[0]);
		exit(0);
	}
	else
	{
		while ((wait_pid = wait(&pid)) > 0)
			;
		close(link[1]);
		read(link[0], output, 50000);
		printf("Output vaut |\n%s|\n", output);
	}
	save_redir(command, output);
	printf("supposed to print once\n");
}

void	redirections(t_env *lkd_env, char **path, char *command)
{
	if (ft_strstr(command, "<<"))
		double_arrow_left(lkd_env, command);
	else if (ft_strchr(command, '<'))
		simple_arrow_left(lkd_env, command);
	else if (ft_strchr(command, '>') || ft_strstr(command, ">>"))
		arrow_right(lkd_env, path, command);
}
