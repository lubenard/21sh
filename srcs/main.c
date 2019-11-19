/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:53:06 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/13 05:13:21 by ymarcill         ###   ########.fr       */
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

	ioctl(0, TIOCGWINSZ, &ws);
	w.ws_col = ws.ws_col;
	w.ws_row = ws.ws_row;
	signal(SIGWINCH, size_handler);
	signal(SIGINT, signalhandler);
}

int			main(int argc, char **argv, char **env)
{
	t_env			*lkd_env;
	t_hist			*lkd_hist;
	t_hustru		*big_struc;
	char			**path;

	(void)argc;
	set_none_canon_mode(0);
	catch_signal();
	lkd_env = get_env(env);
	lkd_hist = new_maillon_hist();
	path = get_path(find_in_env(lkd_env, ft_strdup("PATH")));
	big_struc = fill_huge_struc(lkd_env, lkd_hist, path);
	tcgetattr(0, &big_struc->old_p);
	change_env(big_struc);
	get_option(big_struc, argv);
	isatty(0) ? display_prompt(find_name(lkd_env), find_cur_dir(lkd_env)) : NULL;
	while (ft_read_1(big_struc) == 0)
	{
		parser(big_struc, g_mainline);
		isatty(0) ? display_prompt(find_name(lkd_env), find_cur_dir(lkd_env)) : NULL;
		//display_prompt(find_name(lkd_env), find_cur_dir(lkd_env));
	}
	return (ft_exit(big_struc, big_struc->last_ret));
}
