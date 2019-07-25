/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:40:41 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/13 16:55:44 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	display_prompt(char *username, char *curr_dir)
{
	ft_putstr("\033[31m");
	ft_putstr(username);
	ft_putstr("\033[0m - \033[36m");
	ft_putstr(curr_dir);
	ft_putstr("\033[0m >  ");
}

void	invalid_command(char *command)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(" : command not found ¯\\_(ツ)_/¯\n", 2);
}

int		get_error_exec(char path[6000])
{
	struct stat filestat;

	if (stat(path, &filestat) < 0)
		return (1);
	else if (S_ISDIR(filestat.st_mode))
		return (1);
	return (0);
}

char	*find_cur_dir(t_env *lkd_env)
{
	char *dir;

	dir = find_in_env(lkd_env, ft_strdup("PWD"));
	if (ft_strcmp(dir, ""))
		return (dir);
	return (ft_strdup("???"));
}

char	*find_name(t_env *lkd_env)
{
	char *name;

	name = find_in_env(lkd_env, ft_strdup("USER"));
	if (ft_strcmp(name, ""))
		return (name);
	return (ft_strdup("John Doe"));
}
