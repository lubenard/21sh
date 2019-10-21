/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:53:06 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 14:03:11 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void		change_env(t_hustru *big_struc)
{
	char	*buff[3];
	char	*str;
	int		i;

	buff[0] = "setenv";
	buff[2] = NULL;
	str = find_in_env(big_struc->lkd_env, ft_strdup("SHLVL"));
	if (str == NULL)
	{
		printf("je rentre ici\n");
		buff[1] = "SHLVL=1";
		set_env(big_struc, buff);
	}
	else
	{
		i = ft_atoi(str) + 1;
		free(str);
		str = ft_itoa(i);
		buff[1] = ft_strjoin("SHLVL=", str);
		set_env(big_struc, buff);
		free(buff[1]);
	}
	free(str);
}

t_hustru	*fill_huge_struc(t_env *lkd_env, t_hist *lkd_hist, char **path)
{
	t_hustru	*big_struc;
	char		buff[4097];

	if (!(big_struc = (t_hustru *)malloc(sizeof(t_hustru))))
		return (NULL);
	big_struc->lkd_env = lkd_env;
	big_struc->lkd_hist = lkd_hist;
	big_struc->path = path;
	big_struc->last_ret = 0;
	big_struc->line = NULL;
	big_struc->fds_index = 0;
	big_struc->should_heredoc = 1;
	big_struc->pipe_heredoc = NULL;
	big_struc->history_path = ft_strjoin(getcwd(buff, 4096), "/.history");
	return (big_struc);
}

void		load_from_history(t_hustru *big_struc)
{
	int		fd;
	char	*str;

	if (access(".history", F_OK) != -1)
	{
		fd = open(".history", O_RDONLY);
		while (get_next_line(fd, &str) > 0)
		{
			printf("This line will be added to history:\n%s\n", str);
			save_command(big_struc, str, 0);
			free(str);
		}
		close(fd);
	}
	else
		ft_putendl_fd("-l option : history file has not been found. \
History will not be loaded.", 2);
}

int			get_option(t_hustru *big_struc, char **argv)
{
	if (argv[1])
	{
		if (!ft_strcmp(argv[1], "-l"))
			load_from_history(big_struc);
		else if (!ft_strcmp(argv[1], "-h") || !ft_strcmp(argv[1], "--help"))
			return (print_shell_help());
		else
			return (display_error("option not recognized, please type --help \
to get help\n", NULL));
	}
	return (0);
}

void		size_handler(int i)
{
	struct winsize win;

	signal(SIGWINCH, size_handler);
	i = ioctl(0, TIOCGWINSZ, &win);
	w.ws_col = win.ws_col;
	w.ws_row = win.ws_row;
//	clean_nprint(w.ws_col, i);
}

void		catch_signal(void)
{
	struct winsize ws;
	int		i;

	i = 0;
	ioctl(0, TIOCGWINSZ, &ws);
	w.ws_col = ws.ws_col;
	w.ws_row = ws.ws_row;
	while (i < 38)
	{
		if (i == SIGWINCH || i == SIGINT)
		{
			signal(SIGWINCH, size_handler);
			signal(SIGINT, signalhandler);
		}
		signal(i, SIG_IGN);
		i++;
	}
}

int			main(int argc, char **argv, char **env)
{
	t_env		*lkd_env;
	t_hist		*lkd_hist;
	t_hustru	*big_struc;
	char		**path;

	(void)argc;
	(void)argv;
	catch_signal();
	lkd_env = get_env(env);
	lkd_hist = new_maillon_hist();
	path = get_path(find_in_env(lkd_env, ft_strdup("PATH")));
	big_struc = fill_huge_struc(lkd_env, lkd_hist, path);
	change_env(big_struc);
	if (get_option(big_struc, argv) == 1)
		return (ft_exit(big_struc, 0));
	//if (argv[1])
	//	parser(big_struc, argv[1]);
	display_prompt(find_name(lkd_env), find_cur_dir(lkd_env));
	while (ft_read_1(big_struc) == 0)
	{
	/*	ft_putstr("Derniere ligne de l'historique : ");
		ft_putendl(big_struc->lkd_hist->history);
		t_hist *tmp;
		tmp = big_struc->lkd_hist;
		ft_putendl("L'historique des commandes, de la plus recente a la + vieille");
		while (tmp)
		{
			ft_putendl(tmp->history);
			tmp = tmp->prev;
		}
		ft_putendl("-------------------");*/
		parser(big_struc, g_mainline);
		display_prompt(find_name(lkd_env), find_cur_dir(lkd_env));
	}
	//printf("retour derniere commande vaut %d\n", big_struc->last_ret);
	//heredoc(big_struc, NULL);
	return (ft_exit(big_struc, big_struc->last_ret));
}
