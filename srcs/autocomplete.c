/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 11:20:35 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/03 22:04:18 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	**autocomp_builtins(char **ret, char *to_find, int k)
{
	int e;
	static char	*tab[] = {"env", "cd", "echo", "exit", "setenv", "unsetenv",
	NULL};

	e = 0;
	while (tab[e])
	{
		if (!ft_strncmp(tab[e], to_find, ft_strlen(to_find)))
			ret[k++] = ft_strdup(tab[e]);
		e++;
	}
	ret[k] = NULL;
	return (ret);
}

int		is_builtin(char *to_find)
{
	int			i;
	int			e;
	static char	*tab[] = {"env", "cd", "echo", "exit", "setenv", "unsetenv",
	NULL};

	i = 0;
	e = 0;
	while (tab[e])
	{
		if (!ft_strncmp(tab[e], to_find, ft_strlen(to_find)))
			i++;
		e++;
	}
	return (i);
}

char	**prep_autocomplete2(t_hustru *big_struc, char **ret, char *to_find)
{
	int				i;
	struct dirent	*p_dirent;
	DIR				*p_dir;
	int				k;

	i = 0;
	k = 0;
	while (big_struc->path[i])
	{
		p_dir = opendir(big_struc->path[i]);
		printf("J'ouvre %s\n", big_struc->path[i]);
		while ((p_dirent = readdir(p_dir)))
		{
			//printf("\e[33mJe regarde %s\e[0m dans %s\n", p_dirent->d_name, big_struc->path[i]);
			if (!ft_strncmp(p_dirent->d_name, to_find, ft_strlen(to_find))
			&& !is_builtin(p_dirent->d_name))
			{
				printf("K = %d\n", k);
				printf("\e[32mJ'ajoute |%s|\n\e[0m", p_dirent->d_name);
				ret[k++] = ft_strdup(p_dirent->d_name);
			}
		}
		closedir(p_dir);
		i++;
	}
	ret[k] = NULL;
	i = 0;
	while (ret[i])
		printf("\e[033mMon tableau vaut %s\n\e[0m", ret[i++]);
	return (autocomp_builtins(ret, to_find, k));
}

char	**print_only_one(t_hustru *big_struc, char *to_find)
{
	(void)big_struc;
	ft_putstr_fd(to_find, 0);
	return (NULL);
}

char	**prep_autocomplete(t_hustru *big_struc, char *to_find)
{
	int				i;
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			**ret;
	int				k;

	i = 0;
	k = 0;
	while (big_struc->path[i])
	{
		p_dir = opendir(big_struc->path[i]);
		while ((p_dirent = readdir(p_dir)))
		{
			if (!ft_strncmp(p_dirent->d_name, to_find, ft_strlen(to_find)))
				k++;
		}
		closedir(p_dir);
		i++;
	}
	if (k + is_builtin(to_find) == 1)
		return (print_only_one(big_struc, to_find));
	else
	{
		if (!(ret = malloc(sizeof(char *) * (k + is_builtin(to_find) + 1))))
			return (NULL);
		printf("J'ai malloc de %d + 1\n", k);
		return (prep_autocomplete2(big_struc, ret, to_find));
	}
}

char	*autocomplete_file(void)
{
	return (0);
}

char	*autocomplete(t_hustru *big_struc, char *command)
{
	int		i;
	char	*first_command;
	char **str;

	i = 0;
	if (!command)
		return (0);
	if (ft_strchr(command, ' '))
		return (autocomplete_file());
	first_command = extract_first(command, ' ');
	str = prep_autocomplete(big_struc, first_command);
	i = 0;
	if (str)
	{
		while (str[i])
		printf("Tab[i]= %s\n", str[i++]);
	ft_deltab(str);
	}
	return (0);
}
