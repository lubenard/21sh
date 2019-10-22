/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:05:11 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/22 12:42:37 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	change_env_cd(t_hustru *big_struc, char *old_pwd, char *new_pwd)
{
	char *new_line[3];

	new_line[0] = "setenv";
	new_line[1] = ft_strjoin("PWD=", new_pwd);
	new_line[2] = NULL;
	set_env(big_struc, new_line);
	free(new_line[1]);
	new_line[1] = ft_strjoin("OLDPWD=", old_pwd);
	if (!old_pwd)
		ft_strcat(new_line[1], new_pwd);
	set_env(big_struc, new_line);
	free(new_line[1]);
}

char	*handle_sortcut(t_env *lkd_env, char *path)
{
	if (!ft_strcmp(path, "") || !ft_strcmp(path, "--"))
		path = find_in_env(lkd_env, ft_strdup("HOME"));
	else if (!ft_strcmp(path, "-"))
		path = find_in_env(lkd_env, ft_strdup("OLDPWD"));
	else
		return (ft_strdup(path));
	return (path);
}

int		change_dir(t_hustru *big_struc, char *path)
{
	char *curr_dir;
	char buff_dir[4097];

	curr_dir = getcwd(buff_dir, 4096);
	path = handle_sortcut(big_struc->lkd_env, path);
	if (chdir(path) != 0)
	{
		if (access(path, F_OK) == -1)
			ft_putstr_fd("cd : No such file or directory : ", 2);
		else if (access(path, R_OK) == -1)
			ft_putstr_fd("cd : Permission denied : ", 2);
		else
			ft_putstr_fd("cd : Not a directory : ", 2);
		ft_putendl_fd(path, 2);
		free(path);
		return (1);
	}
	change_env_cd(big_struc, curr_dir, path);
	free(path);
	return (0);
}

int		cd(t_hustru *big_struc, char **command)
{
	int i;

	i = ft_tablen(command) - 1;
	if (i >= 2)
		display_error("cd : Too many arguments\n", NULL);
	if (command[1])
		return (change_dir(big_struc, command[1]));
	else
		return (change_dir(big_struc, ""));
	return (0);
}
