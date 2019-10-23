/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:17:15 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/24 21:25:05 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		i_is(int *prompt, int *coord)
{
	int i;

	if (prompt[0] != coord[0])
		i = coord[1] + (w.ws_col * (coord[0] - prompt[0]) - prompt[1]);
	else
		i = (coord[1]) - prompt[1];
	return (i);
}

int		get_nb_line_quote(char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (str[i++])
	{
		if (str[i] == '\n')
			nb++;
	}
	if (nb == 0)
		return (nb);
	return (nb);
}

void	clean_for_quotes(int *mainindex, int *prompt, int *pos)
{
	int i;
	int gnbl;

	i = 0;
	gnbl = get_nb_line_quote(g_mainline) +
		get_row(0, ft_strlenu(g_mainline), prompt[1]);
	go_first_char(mainindex, prompt, pos);
	ft_putstr_fd("\e[0K", 0);
	while (i < gnbl)
	{
		ft_putstr_fd("\e[B", 0);
		ft_putstr_fd("\e[2K", 0);
		i++;
	}
	while (i-- > 0)
		ft_putstr_fd("\e[A", 0);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*tmp;

	if (!s1)
		return (NULL);
	tmp = ft_strdup(s1);
	if (!tmp)
		return (NULL);
	ft_strdel(&s1);
	s1 = ft_strjoin(s1, s2);
	ft_strdel(&tmp);
	return (s1);
}
