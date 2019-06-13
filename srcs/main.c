/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:53:06 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/13 19:50:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*g_username;
char	*g_curr_dir;

void	change_env(t_env *lkd_env)
{
	char	buff[4096];
	char	*str;
	int		i;

	str = find_in_env(lkd_env, ft_strdup("SHLVL"));
	if (str == NULL)
	{
		ft_strcpy(buff, "setenv SHLVL=1");
		free(str);
		set_env(lkd_env, buff);
	}
	else
	{
		ft_strcpy(buff, "setenv SHLVL=");
		i = ft_atoi(str) + 1;
		free(str);
		set_env(lkd_env, ft_strcat(buff, str = ft_itoa(i)));
		free(str);
	}
}

void	free_after_exit(t_env *lkd_env, t_hist *lkd_hist, char **path)
{
	t_env	*tmp;
	t_hist	*tmp2;
	int		i;

	i = 0;
	while (lkd_env)
	{
		tmp = lkd_env;
		lkd_env = lkd_env->next;
		free(tmp);
	}
	while (lkd_hist)
	{
		tmp2 = lkd_hist;
		lkd_hist = lkd_hist->next;
		free(tmp2);
	}
	if (path != NULL)
	{
		while (path[i])
			free(path[i++]);
		free(path);
	}
}

char	*get_path_hist(void)
{
	char buff[4097];
	char *path;

	path = getcwd(buff, 4096);
	return (path);
}

t_hustru	*fill_huge_struc(t_env *lkd_env, t_hist *lkd_hist, char **path)
{
	t_hustru *big_struc;

	if (!(big_struc = (t_hustru *)malloc(sizeof(t_hustru))))
		return (NULL);
	big_struc->lkd_env = lkd_env;
	big_struc->lkd_hist = lkd_hist;
	big_struc->path = path;
	big_struc->last_ret = 0;
	return (big_struc);
}

int		main(int argc, char **argv, char **env)
{
	t_env		*lkd_env;
	t_hist		*lkd_hist;
	char		**path;
	t_hustru	*huge_struc;

	(void)argc;
	(void)argv;
	lkd_env = get_env(env);
	//display_prompt("user", "mon_path");
	//printf("\n");
	lkd_hist = new_maillon_hist();
	change_env(lkd_env);
	path = get_path(find_in_env(lkd_env, ft_strdup("PATH")));
	huge_struc = fill_huge_struc(lkd_env, lkd_hist, path);
	echo(huge_struc, argv[1]);
	//set_env(lkd_env, "setenv PATH=🙄"); //add setenv PATH=$PATH:/mon/path and not case sensitive
	//print_env(lkd_env, argv[1], path);
	//history(lkd_hist);
	//printf("find rigth path = %s\n", find_path(path, ft_strdup(argv[1])));
	//redirections(lkd_env, path, argv[1]);
	//save_redir("cat auteur > file1 >> file2", "mycontent");
	//handle_pipe(lkd_env, path, argv[1]);
	return (find_exit("exit", huge_struc)); // NOTE: Control D exit wiht 0
	return (0);
}
