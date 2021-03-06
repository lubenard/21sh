/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:13:35 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/23 11:59:30 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Compact command for pipes, because pipe only accept
** char * and not char **
*/

char	*recompact_command(char **tab)
{
	int		i;
	int		e;
	char	*ret;

	i = 0;
	e = 0;
	while (tab[e + 1])
		i += ft_strlen(tab[e++]) + 1;
	i += ft_strlen(tab[e]);
	if (!(ret = ft_strnew(i)))
		return (NULL);
	e = 0;
	while (tab[e + 1])
	{
		ft_strcat(ret, tab[e++]);
		ft_strcat(ret, " ");
	}
	ft_strcat(ret, tab[e]);
	return (ret);
}

/*
** Tranform char * into char *** by splitting it by pipes then by spaces
** Useful for pipes
*/

char	***compact_command(char *command)
{
	char	***ret;
	char	**argv;
	char	*tmp;
	int		i;

	i = 0;
	if (command[ft_strlen(command) - 1] == '|')
		return (NULL);
	argv = ft_strsplit(command, '|');
	if (!(ret = (char ***)malloc(sizeof(char **) * (ft_tablen(argv) + 1))))
		return (NULL);
	while (argv[i])
	{
		tmp = ft_strtrim(argv[i]);
		ret[i] = ft_strsplit(tmp, ' ');
		free(argv[i]);
		i++;
		free(tmp);
	}
	free(argv);
	ret[i] = NULL;
	return (ret);
}

/*
** Creating command for parser, splitting it by semicolon
*/

char	**create_command(char **command, int *i, int *e)
{
	char	**ret;
	int		j;

	j = 0;
	while (command[*i] && ft_strcmp(command[*i], ";"))
		(*i)++;
	if (*i == 0)
	{
		(*i)++;
		if (!(ret = malloc(sizeof(char *) * 2)))
			return (NULL);
		ret[0] = "";
		return (ret);
	}
	if (!(ret = malloc(sizeof(char *) * (*i + 1))))
		return (NULL);
	while (*e != *i)
		ret[j++] = ft_strdup(command[(*e)++]);
	ret[j] = NULL;
	if (command[*i])
		(*i)++;
	return (ret);
}
