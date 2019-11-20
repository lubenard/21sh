/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch21.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:29:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/20 19:55:22 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

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
	big_struc->home_env_var = find_in_env(lkd_env, ft_strdup("HOME"));
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
			if (!ft_strisascii(str))
			{
				free(str);
				continue;
			}
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
