/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/13 17:15:34 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** NOTES : arrow is creating the files before executing command
*/

int		print_error_redirect(char **tab, char *code)
{
	int i;

	i = 0;
	ft_putstr_fd("ymarsh: parse error near ", 2);
	ft_putendl_fd(code, 2);
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (1);
}

char	**prepare_tab(char *command, char signe)
{
	int		i;
	char	**tab;
	char	*tmp;

	i = 0;
	tab = ft_strsplit_redir(command, signe);
	while (tab[i])
	{
		tmp = ft_strdup(tab[i]);
		free(tab[i]);
		tab[i] = ft_strtrim(tmp);
		free(tmp);
		i++;
	}
	return (tab);
}

void	redirections(t_env *lkd_env, char **path, char *command)
{
	if (ft_strstr(command, "<<"))
		double_arrow_left(lkd_env, command);
	else if (ft_strchr(command, '<'))
		simple_arrow_left(lkd_env, command);
	else if (ft_strchr(command, '>') || ft_strstr(command, ">>"))
		arrow_right(lkd_env, path, command);
}
