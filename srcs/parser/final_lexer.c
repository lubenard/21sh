/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:00:20 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/21 23:09:42 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		ft_tablen(char **tab1)
{
	int i;

	i = 0;
	while (tab1 && tab1[i])
		i++;
	return (i);
}

char	**ft_tabncat(char **tab1, char **tab2, int n)
{
	int		i;
	int		j;
	char	**newtab;

	i = 0;
	j = 0;
	newtab = malloc(sizeof(char*) * (ft_tablen(tab1) + ft_tablen(tab2) + 1));
	if (!tab1)
		return (NULL);
	while (tab1[i] && i < n)
		newtab[j++] = ft_strdup(tab1[i++]);
	i = 0;
	while (tab2 && tab2[i])
		newtab[j++] = ft_strdup(tab2[i++]);
	i = n + 1;
	while (tab1 && tab1[i] && i <= ft_tablen(tab1))
		newtab[j++] = ft_strdup(tab1[i++]);
	newtab[j] = NULL;
	return (newtab);
}

char	**fill_maintab(char **tmp1, char **tmp2, int *i, char **tab_q)
{
	ft_deltab(&tab_q);
	tab_q = ft_tabncat(tmp1, NULL, ft_tablen(tmp1));
	*i += ft_tablen(tmp2) - 1;
	ft_deltab(&tmp2);
	ft_deltab(&tmp1);
	return (tab_q);
}

char	**final_lexer(char *line)
{
	t_coord c;
	char	**tab_q;

	ft_bzero(&c, sizeof(c));
	tab_q = main_lexer(line);
	while (tab_q && tab_q[c.i])
	{
		while (tab_q[c.i][c.j])
		{
			if (tab_q[c.i][c.j] == '\"' || tab_q[c.i][c.j] == '\'')
				c.q_stat = c.q_stat == 0 ? 1 : 0;
			if ((tab_q[c.i][c.j] == '>' || tab_q[c.i][c.j] == '<') && !c.q_stat)
			{
				c.tmp2 = lexer_redir(tab_q[c.i]);
				c.tmp1 = ft_tabncat(tab_q, c.tmp2, c.i);
				ft_putendl(c.tmp1[0]);
				tab_q = fill_maintab(c.tmp1, c.tmp2, &c.i, tab_q);
				break ;
			}
			c.j++;
		}
		c.j = 0;
		c.i++;
	}
	return (tab_q);
}
