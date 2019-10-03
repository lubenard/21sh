/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 11:20:35 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/03 17:28:17 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	**autocomp_builtins(char **ret, char *to_find, int k)
{
	if (!ft_strncmp("env", to_find, ft_strlen(to_find)))
		ret[k++] = ft_strdup("env");
	if (!ft_strncmp("cd", to_find, ft_strlen(to_find)))
		ret[k++] = ft_strdup("cd");
	if (!ft_strncmp("echo", to_find, ft_strlen(to_find)))
		ret[k++] = ft_strdup("echo");
	if (!ft_strncmp("exit", to_find, ft_strlen(to_find)))
		ret[k++] = ft_strdup("exit");
	if (!ft_strncmp("setenv", to_find, ft_strlen(to_find)))
		ret[k++] = ft_strdup("setenv");
	if (!ft_strncmp("unsetenv", to_find, ft_strlen(to_find)))
		ret[k++] = ft_strdup("unsetenv");
	ret[k] = NULL;
	return (ret);
}

int		is_builtin(char *to_find)
{
	if (!ft_strcmp("env", to_find) || !ft_strcmp("cd", to_find)
	|| !ft_strcmp("echo", to_find) || !ft_strcmp("exit", to_find)
	|| !ft_strcmp("setenv", to_find) ||!ft_strcmp("unsetenv", to_find))
	{
		printf("\e[31mJe devais rajouter %s mais c'est un builtin\e[0m\n", to_find);
		return (1);
	}
	return (0);
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
				printf("\e[32mJ'ajoute %s\n\e[0m", p_dirent->d_name);
				ret[k++] = ft_strdup(p_dirent->d_name);
			}
		}
		closedir(p_dir);
		i++;
	}
	return(autocomp_builtins(ret, to_find, k));
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
	//k = autocomp_builtins(&ret, to_find, k, 0);
	if (!(ret = malloc(sizeof(char *) * k + 1)))
		return (NULL);
	printf("J'ai malloc de %d\n", k + 1);
	//return (0);
	return (prep_autocomplete2(big_struc, ret, to_find));
}

char	*autocomplete(t_hustru *big_struc, char *command)
{
	int				i;
	char			*first_command;

	i = 0;
	if (!command)
		return (0);
	first_command = extract_first(command, ' ');
	char **str = prep_autocomplete(big_struc, first_command);
	//(void)str;
	i = 0;
	while (str[i])
	{
		ft_putstr("Tab= ");
		ft_putendl(str[i++]);
	}
		//printf("tab = %s\n", str[i++]);
	//ft_deltab(str);
	return (0);
}
