/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:05:11 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/21 17:02:23 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	change_env_cd(t_hustru *big_struc, char *old_pwd, char *new_pwd)
{
	char *new_line[3];

	new_line[0] = "setenv";
	new_line[2] = NULL;
	new_line[1] = ft_strjoin("PWD=", new_pwd);
	set_env(big_struc, new_line);
	free(new_line[1]);
	new_line[1] = ft_strjoin("OLDPWD=", old_pwd);
	if (!old_pwd)
		ft_strcat(new_line[1], new_pwd);
	set_env(big_struc, new_line);
	free(new_line[1]);
}

int		get_shortcut_path(t_env *lkd_env, char **spec_path, char *path)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	if (path[0] == '~' && path[1] == '/' && ft_strlen(path) > 2)
	{
		while (path[2 + i])
			i++;
		str = ft_strsub(path, 2, i);
		free(path);
		path = find_in_env(lkd_env, ft_strdup("HOME"));
		str2 = ft_strjoin(path, "/");
		*spec_path = ft_strjoin(str2, str);
		free(str);
		free(str2);
		free(path);
		return (0);
	}
	return (1);
}

char	*handle_sortcut(t_env *lkd_env, char *path)
{
	char *spec_path;

	if (!get_shortcut_path(lkd_env, &spec_path, path))
		return (spec_path);
	else if (!ft_strcmp(path, "~")
	|| !ft_strcmp(path, "") || !ft_strcmp(path, "--")
	|| !ft_strcmp(path, "~/"))
	{
		free(path);
		path = find_in_env(lkd_env, ft_strdup("HOME"));
	}
	else if (!ft_strcmp(path, "-"))
	{
		free(path);
		path = find_in_env(lkd_env, ft_strdup("OLDPWD"));
	}
	return (path);
}

void	change_dir(t_hustru *big_struc, char *path)
{
	char *curr_dir;
	char buff_dir[4097];
	char buff_dir2[4097];
	char *new_dir;

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
		big_struc->last_ret = 1;
	}
	else
		change_env_cd(big_struc, curr_dir,
		(new_dir = getcwd(buff_dir2, 4096)));
}

int		cd(t_hustru *big_struc, char **command)
{
	if (command[2])
	{
		ft_putstr_fd("cd : Too many arguments\n", 2);
		return (1);
	}
	change_dir(big_struc, command[1]);
	return (0);
}
