/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:53:06 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/22 11:21:22 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void		size_handler(int i)
{
	struct winsize win;

	signal(SIGWINCH, size_handler);
	i = ioctl(0, TIOCGWINSZ, &win);
	w.ws_col = win.ws_col;
	w.ws_row = win.ws_row;
}

void		catch_signal(void)
{
	struct winsize	ws;
	int				i;

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
	catch_signal();
	lkd_env = get_env(env);
	lkd_hist = new_maillon_hist();
	path = get_path(find_in_env(lkd_env, ft_strdup("PATH")));
	big_struc = fill_huge_struc(lkd_env, lkd_hist, path);
	change_env(big_struc);
	get_option(big_struc, argv);
	display_prompt(find_name(lkd_env), find_cur_dir(lkd_env));
	while (ft_read_1(big_struc) == 0)
	{
		parser(big_struc, g_mainline);
		display_prompt(find_name(lkd_env), find_cur_dir(lkd_env));
	}
	return (ft_exit(big_struc, big_struc->last_ret));
}
